#pragma once

#include "math/mat4.h"
#include "math/quaternion.h"
#include "math/vector3.h"

class Transform {
  Vector3 local_position = Vector3::zero;
  Vector3 local_scale = Vector3::one;
  Quaternion local_rotation = Quaternion::identity;

  mutable bool dirty = true;
  mutable Mat4 model;

 public:
  Transform() = default;
  Transform(float x, float y, float z);

  Mat4 ModelMatrix() const;
};