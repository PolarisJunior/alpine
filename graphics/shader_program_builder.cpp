#include "shader_program_builder.h"

#include <gl/glew.h>

#include "shader_program.h"

std::unique_ptr<ShaderProgram> ShaderProgramBuilder::build() {
  int32_t handle = glCreateProgram();
  glLinkProgram(handle);

  int32_t success;
  glGetProgramiv(handle, GL_LINK_STATUS, &success);
  // if (!success) {
  //   exit(EXIT_FAILURE);
  // }
  return std::make_unique<ShaderProgram>(handle);
}