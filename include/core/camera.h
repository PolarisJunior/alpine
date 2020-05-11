#pragma once

#include "math/ray.h"
#include "pjmath/math_defs.hpp"
#include "transform.h"

class Mat4;

class Camera {
 public:
  Transform transform;

  real_t near_clip_plane = 0.1f;
  real_t far_clip_plane = 1000.0f;

  real_t field_of_view = 103.0;

  Mat4 ViewMatrix() const;
  Mat4 ProjectionMatrix() const;
  Mat4 ProjectionViewMatrix() const;

  Mat4 InverseProjectionMatrix() const;

  Ray ScreenPointToRay(real_t x, real_t y) const;
};
