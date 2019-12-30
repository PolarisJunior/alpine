#include "camera.h"

Mat4 Camera::ViewMatrix() const {
  return transform.ModelMatrix().Inverse();
}