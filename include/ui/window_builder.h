
#pragma once

#include <memory>
#include <string>

#include "window.h"

class WindowBuilder {
 public:
  WindowBuilder();

  WindowBuilder& Title(const std::string& t);

  std::unique_ptr<Window> Build() const;

  int32_t width = 800;
  int32_t height = 600;

  int32_t x;
  int32_t y;

  uint32_t flags;

  std::string title;
};