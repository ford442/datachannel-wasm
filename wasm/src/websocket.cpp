/**
 * Copyright (c) 2017-2020 Paul-Louis Ageneau
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "websocket.hpp"

#include <emscripten/emscripten.h>

#include <exception>
#include <memory>

extern "C" {
extern int wsCreateWebSocket(const char *url);
extern void wsDeleteWebSocket(int ws);
extern void wsSetOpenCallback(int ws, void (*openCallback)(void *));
extern void wsSetErrorCallback(int ws, void (*errorCallback)(const char *, void *));
extern void wsSetMessageCallback(int ws, void (*messageCallback)(const char *, int, void *));
extern int wsSendMessage(int ws, const char *buffer, int size);
extern void wsSetUserPointer(int ws, void *ptr);
}

namespace rtc {

void WebSocket::OpenCallback(void *ptr) {
	WebSocket *w = static_cast<WebSocket *>(ptr);
	if (w)
		w->triggerOpen();
}

void WebSocket::ErrorCallback(const char *error, void *ptr) {
	WebSocket *w = static_cast<WebSocket *>(ptr);
	if (w)
		w->triggerError(string(error ? error : "unknown"));
}

void WebSocket::MessageCallback(const char *data, int size, void *ptr) {
	WebSocket *w = static_cast<WebSocket *>(ptr);
	if (w) {
		if (data) {
			if (size >= 0) {
				auto b = reinterpret_cast<const byte *>(data);
				w->triggerMessage(binary(b, b + size));
			} else {
				w->triggerMessage(string(data));
			}
		} else {
			w->close();
			w->triggerClosed();
		}
	}
}

WebSocket::WebSocket() : mId(0), mConnected(false) {}

WebSocket::~WebSocket() { close(); }

void WebSocket::open(const string &url) {
	close();

	mId = wsCreateWebSocket(url.c_str());
	if (!mId)
		throw std::runtime_error("WebSocket not supported");

	wsSetUserPointer(mId, this);
	wsSetOpenCallback(mId, OpenCallback);
	wsSetErrorCallback(mId, ErrorCallback);
	wsSetMessageCallback(mId, MessageCallback);
}

void WebSocket::close() {
	mConnected = false;
	if (mId) {
		wsDeleteWebSocket(mId);
		mId = 0;
	}
}

bool WebSocket::isOpen() const { return mConnected; }

bool WebSocket::isClosed() const { return mId == 0; }

bool WebSocket::send(message_variant message) {
	if (!mId)
		return false;

	return std::visit(
	    overloaded{[this](const binary &b) {
		               auto data = reinterpret_cast<const char *>(b.data());
		               return wsSendMessage(mId, data, int(b.size())) >= 0;
	               },
	               [this](const string &s) { return wsSendMessage(mId, s.c_str(), -1) >= 0; }},
	    std::move(message));
}

bool WebSocket::send(const byte *data, size_t size) {
	if (!mId)
		return false;

	return wsSendMessage(mId, reinterpret_cast<const char *>(data), int(size)) >= 0;
}

void WebSocket::triggerOpen() {
	mConnected = true;
	Channel::triggerOpen();
}

} // namespace rtc
