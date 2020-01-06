#pragma once

#include <array>
#include <string>

class Skybox {
 public:
  Skybox();
  Skybox(const std::array<std::string, 6>& face_files);

  void Render();

  uint32_t cube_map_id;
};