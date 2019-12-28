#pragma once

#include <memory>

class ShaderProgram;

class ShaderProgramBuilder {
 public:
  std::unique_ptr<ShaderProgram> build();
};