#include "math/mat4.h"

#include <glm/detail/qualifier.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include "math/quaternion.h"

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

Mat4 Mat4::operator*(const Mat4& rhs) const {
  Mat4 m;
  m.glm_mat = glm_mat * rhs.glm_mat;
  return m;
}

pjmath::Vector3 Mat4::operator*(const pjmath::Vector3& rhs) const {
  glm::vec3 glm_vec = glm_mat * glm::vec4(rhs.x, rhs.y, rhs.z, 1);
  return {glm_vec.x, glm_vec.y, glm_vec.z};
}

Mat4& Mat4::operator*=(const Mat4& rhs) {
  *this = *this * rhs;
  return *this;
}

const real_t* Mat4::Data() const {
  return data.data();
}

Mat4 Mat4::Inverse() const {
  Mat4 m;
  m.glm_mat = glm::inverse(glm_mat);
  return m;
}

// void Mat4::SetTranslate(real_t x, real_t y, real_t z) {
//   rows[3][0] = x;
//   rows[3][1] = y;
//   rows[3][2] = z;
// }

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

Mat4 Mat4::Translate(const pjmath::Vector3& vec) {
  return Translate(vec.x, vec.y, vec.z);
}

Mat4 Mat4::Rotate(real_t rads, const pjmath::Vector3& axis) {
  Mat4 m = Mat4::identity;
  m.glm_mat = glm::rotate(rads, glm::vec3(axis.x, axis.y, axis.z));
  return m;
}

Mat4 Mat4::Rotate(const Quaternion& q) {
  glm::qua<real_t, glm::qualifier::defaultp> gq;
  gq.x = q.x;
  gq.y = q.y;
  gq.z = q.z;
  gq.w = q.w;

  Mat4 m;
  m.glm_mat = glm::toMat4(gq);
  return m;
}

Mat4 Mat4::Scale(real_t x, real_t y, real_t z) {
  Mat4 m = Mat4::identity;
  m.glm_mat = glm::scale(glm::vec3(x, y, z));
  // m.SetScale(x, y, z);
  return m;
}

Mat4 Mat4::Scale(const pjmath::Vector3& vec) {
  return Scale(vec.x, vec.y, vec.z);
}
