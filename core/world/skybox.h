#pragma once

#include <array>
#include <memory>
#include <string>

class ShaderProgram;
class Camera;

class Skybox {
 public:
  Skybox();
  Skybox(const std::array<std::string, 6>& face_files,
         std::unique_ptr<ShaderProgram> prog);

  void Render(const Camera& cam);

  uint32_t cube_map_id;

 private:
  std::unique_ptr<ShaderProgram> shader_program;
};