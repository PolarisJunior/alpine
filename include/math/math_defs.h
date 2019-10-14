
#pragma once

#ifdef REAL_T_IS_DOUBLE
typedef double real_t;
#else
typedef float real_t;
#endif

constexpr real_t CMP_EPSILON = static_cast<real_t>(0.00001);
constexpr real_t PI = static_cast<real_t>(3.14159265);
