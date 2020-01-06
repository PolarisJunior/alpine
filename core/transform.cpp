#include "transform.h"

// Transform::Transform(Transform&& other) {

// }

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

void Transform::Translate(const Vector3& vec) {
  local_position += vec;
}