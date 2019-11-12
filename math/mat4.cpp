#include "mat4.h"

#include <mat4x4.hpp>

#ifdef REAL_T_IS_DOUBLE
typedef glm::dmat4x4 mat_t;
#else
typedef glm::mat4x4 mat_t;
#endif

#define GLM_MAT_CONST(x) reinterpret_cast<const mat_t*>(&x)
#define GLM_MAT(x) reinterpret_cast<mat_t*>(&x)
#define ALPINE_MAT(x) reinterpret_cast<Mat4*>(&x)

const Mat4 Mat4::identity = Mat4{};

Mat4::Mat4() : Mat4{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1} {}

Mat4::Mat4(real_t x0,
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
           real_t w3)
    : values{x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3} {}

real_t Mat4::operator[](int32_t i) const {
  return values.array[i];
}

Mat4 Mat4::inverse() const {
  return Mat4{*ALPINE_MAT(glm::inverse(*GLM_MAT_CONST(values)))};
}