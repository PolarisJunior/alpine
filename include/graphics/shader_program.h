#pragma once;

#include <cstdint>
#include <string>

class Mat4;

class ShaderProgram {
  int32_t handle;

 public:
  ShaderProgram(int32_t handle) : handle(handle) {}
  ~ShaderProgram();

  void Use();

  void SetUniform(const std::string& name, float f);
  void SetUniform(const std::string& name, int32_t v);
  void SetUniform(const std::string& name, const Mat4& m);
};