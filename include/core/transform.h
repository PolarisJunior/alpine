#pragma once

#include "math/mat4.h"
#include "math/quaternion.h"
#include "pjmath/vector.hpp"

class Transform {
  pjmath::Vector3 local_position = pjmath::Vector3::zero;
  pjmath::Vector3 local_scale = pjmath::Vector3::one;
  Quaternion local_rotation = Quaternion::identity;

  mutable bool dirty = true;
  mutable Mat4 model;

 public:
  Transform() = default;
  Transform(float x, float y, float z)
      : local_position(pjmath::Vector3{x, y, z}){};

  void Translate(const pjmath::Vector3& vec);
  void Rotate(real_t rads, const pjmath::Vector3& axis);

  // Locals
  pjmath::Vector3 Position() const;
  pjmath::Vector3 Scale() const;
  Quaternion Rotation() const;

  // Globals
  pjmath::Vector3 GlobalPosition() const;
  pjmath::Vector3 GlobalScale() const;
  Quaternion GlobalRotation() const;

  Mat4 ModelMatrix() const;
  Mat4 InverseModelMatrix() const;
};
