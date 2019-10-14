
#include "ui/window.h"

#include <SDL.h>

Window::Window() : raw_window(nullptr) {}

Window::Window(const std::string& title,
               int32_t x,
               int32_t y,
               int32_t w,
               int32_t h,
               uint32_t flags)
    : width(w), height(h) {
  raw_window =
      static_cast<void*>(SDL_CreateWindow(title.c_str(), x, y, w, h, flags));
}

Window::~Window() {
  SDL_DestroyWindow(static_cast<SDL_Window*>(raw_window));
}

void Window::SwapWindow() {
  SDL_GL_SwapWindow(static_cast<SDL_Window*>(raw_window));
}
