#include "core/meshes/mesh.h"

#include <algorithm>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include "core/io/file.h"

Mesh Mesh::FromFile(const std::string& path) {
  using json = nlohmann::json;
  File file{path};
  json j = json::parse(file.ReadString());
  std::cout << j["triangles"].size() << " " << j["vertices"].size()
            << std::endl;
  std::vector<float> verts(j["vertices"].size());
  std::transform(j["vertices"].begin(), j["vertices"].end(), verts.begin(),
                 [](auto vert) { return (float)vert; });
  std::transform(j["triangles"].begin(), j["triangles"].end(),
                 j["triangles"].begin(),
                 [](auto idx) { return idx >= 0 ? idx : -idx - 1; });
  return Mesh{verts, j["triangles"], j["normals"], j["uvs"]};
}