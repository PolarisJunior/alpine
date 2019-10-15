#pragma once

#include "math_defs.h"

class Vector3 {
 public:
  union {
    struct {
      real_t x;
      real_t y;
      real_t z;
    };

    real_t coord[3];
  };

  Vector3() = default;
  Vector3(real_t x, real_t y, real_t z);

  Vector3 operator+(const Vector3& other) const;
  Vector3 operator-(const Vector3& other) const;

  Vector3 operator*(real_t scale) const;
  Vector3 operator*(const Vector3& other) const;

  Vector3 operator/(real_t divisor) const;
  Vector3 operator/(const Vector3& other) const;

  Vector3 operator-() const;

  Vector3& operator+=(const Vector3& other);
  Vector3& operator-=(const Vector3& other);
  Vector3& operator*=(const Vector3& other);
  Vector3& operator*=(real_t scale);
  Vector3& operator/=(real_t divisor);

  bool operator==(const Vector3& other) const;
  bool operator!=(const Vector3& other) const { return !(*this == other); }

  friend std::ostream& operator<<(std::ostream& out, const Vector3& vec) {
    return out << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  }

  Vector3 Normalized() const;
  Vector3& Normalize();
  real_t Length() const;
  real_t Magnitude() const;
  bool Equals(const Vector3& other, real_t delta = CMP_EPSILON) const;

  real_t Dot(const Vector3& other) const;
  Vector3 Cross(const Vector3& other) const;

  real_t Pitch() const;
  real_t Yaw() const;
  real_t Roll() const;

  static Vector3 zero;
  static Vector3 one;
  static Vector3 right;
  static Vector3 left;
  static Vector3 up;
  static Vector3 down;
  static Vector3 front;
  static Vector3 back;
  static Vector3 forward;
  static Vector3 backward;
};

inline Vector3::Vector3(real_t x, real_t y, real_t z) : x(x), y(y), z(z) {}

inline Vector3 Vector3::operator+(const Vector3& other) const {
  return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}

inline Vector3 Vector3::operator-(const Vector3& other) const {
  return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}

inline Vector3 Vector3::operator-() const {
  return Vector3(-x, -y, -z);
}

inline Vector3 Vector3::operator*(real_t scale) const {
  return Vector3(this->x * scale, this->y * scale, this->z * scale);
}

inline Vector3 Vector3::operator*(const Vector3& other) const {
  return Vector3(this->x * other.x, this->y * other.y, this->z * other.z);
}

inline Vector3 Vector3::operator/(real_t divisor) const {
  return Vector3(this->x / divisor, this->y / divisor, this->z / divisor);
}

inline Vector3 Vector3::operator/(const Vector3& other) const {
  return Vector3(this->x / other.x, this->y / other.y, this->z / other.z);
}

inline Vector3& Vector3::operator+=(const Vector3& other) {
  this->x += other.x;
  this->y += other.y;
  this->z += other.z;
  return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& other) {
  this->x -= other.x;
  this->y -= other.y;
  this->z -= other.z;
  return *this;
}

inline Vector3& Vector3::operator*=(real_t scale) {
  this->x *= scale;
  this->y *= scale;
  this->z *= scale;
  return *this;
}

inline Vector3& Vector3::operator*=(const Vector3& other) {
  this->x *= other.x;
  this->y *= other.y;
  this->z *= other.z;
  return *this;
}

inline Vector3& Vector3::operator/=(real_t divisor) {
  this->x /= divisor;
  this->y /= divisor;
  this->z /= divisor;
  return *this;
}

inline bool Vector3::operator==(const Vector3& other) const {
  return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
}

inline Vector3 Vector3::Normalized() const {
  Vector3 ret = *this;
  ret.Normalize();
  return ret;
}

inline Vector3& Vector3::Normalize() {
  if (Length() > 0) {
    *this /= Length();
  }
  return *this;
}

inline real_t Vector3::Length() const {
  return static_cast<real_t>(sqrt(Dot(*this)));
}

inline real_t Vector3::Magnitude() const {
  return Length();
}

inline bool Vector3::Equals(const Vector3& other, real_t delta) const {
  return fabs(this->x - other.x) + fabs(this->y - other.y) +
             fabs(this->z - other.z) <
         delta;
}

inline real_t Vector3::Dot(const Vector3& other) const {
  return this->x * other.x + this->y * other.y + this->z * other.z;
}

inline Vector3 Vector3::Cross(const Vector3& other) const {
  return Vector3(y * other.z - z * other.y, z * other.x - x * other.z,
                 x * other.y - y * other.x);
}

inline real_t Vector3::Pitch() const {
  return this->x;
}

inline real_t Vector3::Yaw() const {
  return this->y;
}

inline real_t Vector3::Roll() const {
  return this->z;
}

inline Vector3 Vector3::zero = Vector3(0, 0, 0);
inline Vector3 Vector3::one = Vector3(1, 1, 1);
inline Vector3 Vector3::right = Vector3(1, 0, 0);
inline Vector3 Vector3::left = Vector3(-1, 0, 0);
inline Vector3 Vector3::up = Vector3(0, 1, 0);
inline Vector3 Vector3::down = Vector3(0, -1, 0);
inline Vector3 Vector3::forward = Vector3(0, 0, 1);
inline Vector3 Vector3::backward = Vector3(0, 0, -1);