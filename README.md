# datachannel-wasm - C++ WebRTC Data Channels for WebAssembly in browsers

datachannel-wasm is a C++ WebRTC Data Channels and WebSocket wrapper for [Emscripten](https://emscripten.org/) compatible with [libdatachannel](https://github.com/paullouisageneau/libdatachannel).

datachannel-wasm exposes the same API as [libdatachannel](https://github.com/paullouisageneau/libdatachannel), and therefore allows to compile the same C++ code using DataChannels and WebSockets to WebAssembly for browsers in addition to native targets supported by libdatachannel. The interface is only a subset of the one of [libdatachannel](https://github.com/paullouisageneau/libdatachannel), in particular, tracks and media transport are not supported. See what is available in [wasm/include](https://github.com/paullouisageneau/datachannel-wasm/tree/master/wasm/include/rtc).

These wrappers were originally written for my multiplayer game [Convergence](https://github.com/paullouisageneau/convergence) and were extracted from there to be easily reusable.

datachannel-wasm is licensed under LGPLv2, see [LICENSE](https://github.com/paullouisageneau/datachannel-wasm/blob/master/LICENSE).

## Installation

You just need to add datachannel-wasm as a submodule in your Emscripten project:
```bash
$ git submodule add https://github.com/paullouisageneau/datachannel-wasm.git deps/datachannel-wasm
$ git submodule update --init --recursive
```

CMakeLists.txt:
```cmake
[...]
add_subdirectory(deps/datachannel-wasm EXCLUDE_FROM_ALL)
target_link_libraries(YOUR_PROJECT datachannel-wasm)
```

Since datachannel-wasm is compatible with [libdatachannel](https://github.com/paullouisageneau/libdatachannel), you can easily leverage both to make the same C++ code compile to native (including MacOS and Windows):

```bash
$ git submodule add https://github.com/paullouisageneau/datachannel-wasm.git deps/datachannel-wasm
$ git submodule add https://github.com/paullouisageneau/libdatachannel.git deps/libdatachannel
$ git submodule update --init --recursive
```

CMakeLists.txt:
```cmake
if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
    add_subdirectory(deps/datachannel-wasm EXCLUDE_FROM_ALL)
    target_link_libraries(YOUR_PROJECT datachannel-wasm)
else()
    option(NO_MEDIA "Disable media support in libdatachannel" ON)
    add_subdirectory(deps/libdatachannel EXCLUDE_FROM_ALL)
    target_link_libraries(YOUR_PROJECT datachannel-static)
endif()
```

## Building

Building requires that you have [emsdk](https://github.com/emscripten-core/emsdk) installed and activated in your environment:
```bash
$ cmake -B build -DCMAKE_TOOLCHAIN_FILE=$EMSDK/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
$ cd build
$ make -j2
```

