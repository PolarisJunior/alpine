#include "math/quaternion.h"

#include "math/mat4.h"
#include "pjmath/math_funcs.hpp"

Quaternion::Quaternion(real_t rf_angle, const pjmath::Vector3& rk_axis) {
  pjmath::Vector3 axis = rk_axis.Normalized();

  real_t f_half_angle(0.5 * rf_angle);
  real_t f_sin = pjmath::Sin(f_half_angle);
  w = pjmath::Cos(f_half_angle);
  x = f_sin * axis.x();
  y = f_sin * axis.y();
  z = f_sin * axis.z();
}

Mat4 Quaternion::ToMatrix() const {
  return Mat4::Rotate(*this);
}

Quaternion Quaternion::Inverse() const {
  float norm = w * w + x * x + y * y + z * z;
  if (norm > 0.0) {
    float inv_norm = 1.0 / norm;
    return Quaternion(-x * inv_norm, -y * inv_norm, -z * inv_norm,
                      w * inv_norm);
  }
  // Error
  return Quaternion(0, 0, 0, 0);
}

pjmath::Vector3 Quaternion::operator*(const pjmath::Vector3& v) const {
  pjmath::Vector3 q{x, y, z};
  pjmath::Vector3 t = q.Cross(v) * 2.0f;
  return v + (t * w) + q.Cross(t);
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const {
  return Quaternion(w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y,
                    w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z,
                    w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x,
                    w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z);
}

Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
  *this = *this * rhs;
  return *this;
}

const Quaternion Quaternion::identity(0, 0, 0, 1);
const Quaternion Quaternion::zero(0, 0, 0, 0);
