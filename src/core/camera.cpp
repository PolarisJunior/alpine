#include "core/camera.h"

#include "core/program.h"

#include <glm/mat4x4.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "math/math_funcs.h"

Mat4 Camera::ViewMatrix() const {
  return transform.InverseModelMatrix();
}

Mat4 Camera::ProjectionMatrix() const {
  Mat4 m;
  glm::mat4 proj = glm::perspectiveFovLH(
      Math::ToRads(field_of_view),
      static_cast<real_t>(Program::GetMainWindow().Width()),
      static_cast<real_t>(Program::GetMainWindow().Height()), near_clip_plane,
      far_clip_plane);
  memcpy(&m, &proj, sizeof(m));
  return m;
}

Mat4 Camera::ProjectionViewMatrix() const {
  return ProjectionMatrix() * ViewMatrix();
}

Mat4 Camera::InverseProjectionMatrix() const {
  return ProjectionMatrix().Inverse();
}

Ray Camera::ScreenPointToRay(real_t x, real_t y) const {
  // NEEDS TESTING
  Vector3 ndc((x / Program::GetMainWindow().Width()) * 2,
              -(y / Program::GetMainWindow().Height() - .5) * 2, -1);
  Ray ray{transform.GlobalPosition(), transform.GlobalRotation().ToMatrix() *
                                          InverseProjectionMatrix() * ndc};
  return ray;
}