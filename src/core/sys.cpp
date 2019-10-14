#include "core/sys.h"
#include <SDL.h>

void Sys::Delay(real_t t) {
  SDL_Delay(static_cast<uint32_t>(t * 1000));
}

void Sys::Delay(std::chrono::milliseconds ms) {
  SDL_Delay(ms.count());
}