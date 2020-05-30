#include "core/transform.h"

Mat4 Transform::ModelMatrix() const {
  if (!dirty) {
    return model;
  } else {
    model = Mat4::Translate(local_position) * local_rotation.ToMatrix() *
            Mat4::Scale(local_scale);
    dirty = false;
    return model;
  }
}

Mat4 Transform::InverseModelMatrix() const {
  return ModelMatrix().Inverse();
}

void Transform::Translate(const pjmath::Vector3& vec) {
  local_position += vec;
  dirty = true;
}

void Transform::Rotate(real_t rads, const pjmath::Vector3& axis) {
  local_rotation *= Quaternion{rads, axis};
  dirty = true;
}

pjmath::Vector3 Transform::Position() const {
  return local_position;
  // return local_position;
}

pjmath::Vector3 Transform::GlobalPosition() const {
  // TODO support global position
  return Position();
}

Quaternion Transform::Rotation() const {
  return local_rotation;
}

Quaternion Transform::GlobalRotation() const {
  // TODO
  return Rotation();
}
