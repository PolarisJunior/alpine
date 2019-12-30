#pragma once

#include "mat4.h"
#include "math_defs.h"
#include "vector3.h"

class Mat4;

class Quaternion {
 public:
  float x = 0;
  float y = 0;
  float z = 0;
  float w = 1;

  Quaternion() = default;
  Quaternion(real_t x, real_t y, real_t z, real_t w) : x(x), y(y), z(z), w(w) {}
  Quaternion(real_t rf_angle, const Vector3& rk_axis);

  Quaternion Inverse() const;
  Mat4 ToMatrix() const;

  Vector3 operator*(const Vector3& v) const;
  Quaternion operator*(const Quaternion& rhs) const;
  Quaternion& operator*=(const Quaternion& rhs);

  static const Quaternion identity;
  static const Quaternion zero;
};