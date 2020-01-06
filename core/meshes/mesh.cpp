#include "mesh.h"

#include <nlohmann/json.hpp>
#include "core/io/file.h"

Mesh Mesh::FromFile(const std::string& path) {
  using json = nlohmann::json;
  File file{path};
  json j = json::parse(file.ReadString());
  return Mesh{j["vertices"], j["triangles"], j["normals"], j["uvs"]};
}