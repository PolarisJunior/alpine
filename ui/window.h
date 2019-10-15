#pragma once

#include <string>

class Window {
 public:
  Window(const std::string& title,
         int32_t x,
         int32_t y,
         int32_t w,
         int32_t h,
         uint32_t flags);

  ~Window();

  Window& operator=(Window&& other);
  friend void swap(Window& first, Window& second);

  void* raw_window;
};