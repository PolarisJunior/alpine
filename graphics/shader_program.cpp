#include "shader_program.h"

#include <gl/glew.h>

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