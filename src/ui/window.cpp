
#include "ui/window.h"

#include <SDL.h>
#include <SDL_opengl.h>

struct Window::WindowImpl {
  SDL_Window* raw_window;
};

Window::Window() : impl(nullptr) {}

Window::Window(const std::string& title,
               int32_t x,
               int32_t y,
               int32_t w,
               int32_t h,
               uint32_t flags)
    : impl(std::make_unique<WindowImpl>()), width(w), height(h) {
  impl->raw_window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
}

Window::~Window() {
  SDL_DestroyWindow(impl->raw_window);
}

void Window::SwapWindow() {
  SDL_GL_SwapWindow(impl->raw_window);
}

void Window::InitGlContext() {
  SDL_GLContext context = SDL_GL_CreateContext(impl->raw_window);
}
