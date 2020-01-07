#pragma once
#include <memory>
#include <string>

class ShaderProgram;

class Material {
 public:
  Material(std::unique_ptr<ShaderProgram> program);
  Material(const std::string& vert_file, const std::string& frag_file);
  Material(const Material&);

  std::shared_ptr<ShaderProgram> shader;
};