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

  void Translate(const Vector3& vec);

  // Locals
  Vector3 Position() const;
  Vector3 Scale() const;
  Quaternion Rotation() const;

  // Globals
  Vector3 GlobalPosition() const;
  Vector3 GlobalScale() const;
  Quaternion GlobalRotation() const;

  Mat4 ModelMatrix() const;
  Mat4 InverseModelMatrix() const;
};