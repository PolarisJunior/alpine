
#include "window.h"

#include <SDL.h>

Window::Window() : raw_window(nullptr) {}

Window::Window(const std::string& title,
               int32_t x,
               int32_t y,
               int32_t w,
               int32_t h,
               uint32_t flags) {
  raw_window =
      static_cast<void*>(SDL_CreateWindow(title.c_str(), x, y, w, h, flags));
}

Window::~Window() {
  SDL_DestroyWindow(static_cast<SDL_Window*>(raw_window));
}

Window& Window::operator=(Window&& other) {
  swap(*this, other);
  return *this;
}

void swap(Window& first, Window& second) {
  using std::swap;
  swap(first.raw_window, second.raw_window);
}