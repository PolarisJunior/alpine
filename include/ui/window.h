#pragma once

#include <cstdint>
#include <memory>
#include <string>

class Window {
  struct WindowImpl;

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

  void InitGlContext();

  Window& operator=(Window&& other);

 private:
  std::unique_ptr<WindowImpl> impl;
  int32_t width;
  int32_t height;
};
