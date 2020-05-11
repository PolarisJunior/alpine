#pragma once
#include "pjmath/math_defs.hpp"
#include "pjmath/vector.hpp"

struct Ray {
  pjmath::Vector3 origin;
  pjmath::Vector3 direction;
};
