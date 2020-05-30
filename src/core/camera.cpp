#include "core/camera.h"

#include <glm/mat4x4.hpp>

#include "core/program.h"
#include "glm/gtc/matrix_transform.hpp"
#include "pjmath/math_funcs.hpp"

Mat4 Camera::ViewMatrix() const {
  return transform.InverseModelMatrix();
}

Mat4 Camera::ProjectionMatrix() const {
  Mat4 m;
  glm::mat4 proj = glm::perspectiveFovLH(
      pjmath::ToRads(field_of_view),
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
  pjmath::Vector3 ndc =
      transform.GlobalRotation().ToMatrix() * InverseProjectionMatrix() *
      pjmath::Vector3{
          static_cast<real_t>((x / Program::GetMainWindow().Width()) * 2.0),
          static_cast<real_t>(-(y / Program::GetMainWindow().Height() - .5) *
                              2),
          static_cast<real_t>(-1)};
  Ray ray{transform.GlobalPosition(), ndc};
  return ray;
}
