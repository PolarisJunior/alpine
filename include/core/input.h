#pragma once

#include <cstdint>

class Input {
 public:
  static bool GetKey(uint32_t keyCode);
  static bool GetKeyDown(uint32_t keyCode);
  static bool GetKeyUp(uint32_t keyCode);

  static bool GetMouseButton();
  static bool GetMouseButtonDown();
  static bool GetMouseButtonUp();
};