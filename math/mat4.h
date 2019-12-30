#pragma once

#include <array>

#include "math/math_defs.h"
#include "math/vector3.h"

#include <glm/mat4x4.hpp>

#ifdef REAL_T_IS_DOUBLE
typedef glm::dmat4x4 mat_t;
#else
typedef glm::mat4x4 mat_t;
#endif

class Quaternion;

class Mat4 {
  union {
    std::array<real_t, 16> data;
    std::array<std::array<real_t, 4>, 4> rows;
    mat_t glm_mat;
  };

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

  // At the time of writing, Mat4 is column major to
  // comply with OpenGL.
  real_t operator[](int32_t i) const;

  Mat4 operator*(const Mat4& rhs);

  Mat4& operator*=(const Mat4& rhs);

  const real_t* Data() const;

  Mat4 Inverse() const;

  void SetScale(real_t x, real_t y, real_t z);

  static Mat4 Translate(real_t x, real_t y, real_t z);
  static Mat4 Translate(const Vector3& vec);

  static Mat4 Rotate(real_t rads, const Vector3& axis);
  static Mat4 Rotate(const Quaternion& q);

  static Mat4 Scale(real_t x, real_t y, real_t z);
  static Mat4 Scale(const Vector3& vec);

  static const Mat4 identity;
};