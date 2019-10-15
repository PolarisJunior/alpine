#pragma once

#include <chrono>
#include "math/math_defs.h"

class Sys {
 public:
  static void Delay(real_t t);
  static void Delay(std::chrono::milliseconds ms);
};