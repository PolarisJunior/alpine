#include "transform.h"

Mat4 Transform::ModelMatrix() const {
  if (!dirty) {
    return model;
  } else {
    return model;
  }
}