#pragma once

#include <string>

#include <cstdint>

class Window {
  int32_t width;
  int32_t height;

 public:
  Window();
  Window(const std::string& title,
         int32_t x,
         int32_t y,
         int32_t w,
         int32_t h,
         uint32_t flags);

  ~Window();

  void SwapWindow();

  int32_t Width() const { return width; };
  int32_t Height() const { return height; };

  Window& operator=(Window&& other);

  void* raw_window;
};
