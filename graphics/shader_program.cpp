#include "shader_program.h"

#include <gl/glew.h>

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(handle);
}

void ShaderProgram::Use() {
  glUseProgram(handle);
}