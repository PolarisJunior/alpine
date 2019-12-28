#pragma once;

#include <cstdint>

class ShaderProgram {
  int32_t handle;

 public:
  ShaderProgram(int32_t handle) : handle(handle) {}
  ~ShaderProgram();

  void Use();
};