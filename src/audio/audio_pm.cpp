#include "../../include/audio/audio_sdl.hpp"

Audio audio;

extern "C" {

EM_BOOL pl(){
audio.plt();
return EM_TRUE;
}
  
}

EMSCRIPTEN_BINDINGS(my_video_module) {
emscripten::function("setPCMDataHandler", &audio_module_set_js_pcm_handler);
}
