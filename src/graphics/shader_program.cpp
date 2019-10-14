#include "graphics/shader_program.h"

#include <gl/glew.h>

#include "math/mat4.h"

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(handle);
}

void ShaderProgram::Use() {
  glUseProgram(handle);
}

void ShaderProgram::SetUniform(const std::string& name, float f) {
  glUniform1f(glGetUniformLocation(handle, name.c_str()), f);
}

void ShaderProgram::SetUniform(const std::string& name, int32_t v) {
  glUniform1i(glGetUniformLocation(handle, name.c_str()), v);
}

void ShaderProgram::SetUniform(const std::string& name, const Mat4& m) {
  glUniformMatrix4fv(glGetUniformLocation(handle, name.c_str()), 1, GL_FALSE,
                     m.Data());
}