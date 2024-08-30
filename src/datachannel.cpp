#include <emscripten.h>
#include <emscripten/bind.h>

#include "../wasm/include/rtc/rtc.hpp"

int main(){
  
rtc::Preload();
  
EM_ASM({
console.log('load');
  
});

return 0;
}
