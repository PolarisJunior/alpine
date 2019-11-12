#pragma once

#include <array>

#include "math/math_defs.h"
#include "math/vector3.h"

class Mat4 {
  union {
    std::array<real_t, 16> array;
    std::array<std::array<real_t, 4>, 4> rows;
  } values;

 public:
  Mat4();
  Mat4(real_t x0,
       real_t y0,
       real_t z0,
       real_t w0,

       real_t x1,
       real_t y1,
       real_t z1,
       real_t w1,

       real_t x2,
       real_t y2,
       real_t z2,
       real_t w2,

       real_t x3,
       real_t y3,
       real_t z3,
       real_t w3);

  real_t operator[](int32_t i) const;

  Mat4 inverse() const;

  static const Mat4 identity;
};