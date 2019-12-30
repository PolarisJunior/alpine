#include "mat4.h"

#include <glm/gtx/transform.hpp>

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
    : data{x0, y0, z0, w0, x1, y1, z1, w1, x2, y2, z2, w2, x3, y3, z3, w3} {}

real_t Mat4::operator[](int32_t i) const {
  return data[i];
}

const real_t* Mat4::Data() const {
  return data.data();
}

Mat4 Mat4::Inverse() const {
  return Mat4{*ALPINE_MAT(glm::inverse(*GLM_MAT_CONST(data)))};
}

void Mat4::SetTrans(real_t x, real_t y, real_t z) {
  rows[3][0] = x;
  rows[3][1] = y;
  rows[3][2] = z;
}

void Mat4::SetScale(real_t x, real_t y, real_t z) {
  rows[0][0] = x;
  rows[1][1] = y;
  rows[2][2] = z;
}

Mat4 Mat4::Translate(real_t x, real_t y, real_t z) {
  Mat4 m = Mat4::identity;
  m.glm_mat = glm::translate(glm::vec3(x, y, z));
  // m.SetTrans(x, y, z);
  return m;
}

Mat4 Mat4::Rotate(real_t rads, const Vector3& axis) {
  Mat4 m = Mat4::identity;
  m.glm_mat = glm::rotate(rads, glm::vec3(axis.x, axis.y, axis.z));
  return m;
}

Mat4 Mat4::Scale(real_t x, real_t y, real_t z) {
  Mat4 m = Mat4::identity;
  m.glm_mat = glm::scale(glm::vec3(x, y, z));
  // m.SetScale(x, y, z);
  return m;
}