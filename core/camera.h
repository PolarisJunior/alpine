#pragma once

#include "math/mat4.h"
#include "math/math_defs.h"
#include "transform.h"

class Camera {
 public:
  Transform transform;

  real_t near_clip_plane = 0.1f;
  real_t far_clip_plane = 1000.0f;

  real_t field_of_view = 103.0;

  Mat4 ViewMatrix() const;
};