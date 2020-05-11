#pragma once

#include <chrono>

#include "pjmath/math_defs.hpp"

class Sys {
 public:
  static void Delay(real_t t);
  static void Delay(std::chrono::milliseconds ms);
};
