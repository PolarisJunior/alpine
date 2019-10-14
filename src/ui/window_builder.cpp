#include "ui/window_builder.h"

#include <SDL.h>

WindowBuilder::WindowBuilder()
    : x(SDL_WINDOWPOS_UNDEFINED),
      y(SDL_WINDOWPOS_UNDEFINED),
      flags(SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL) {}

WindowBuilder& WindowBuilder::Title(const std::string& t) {
  title = t;
  return *this;
}

std::unique_ptr<Window> WindowBuilder::Build() const {
  return std::make_unique<Window>(title, x, y, 800, 600, flags);
}