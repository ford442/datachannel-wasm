#include <emscripten.h>
#include <emscripten/bind.h>

int main(){
  
rtc::Preload();
  
EM_ASM({
console.log('load');
  
});

return 0;
}
