#pragma once

#include <string>
#include <vector>

class Mesh {
 public:
  Mesh() = default;
  Mesh(const std::vector<float>& vert,
       const std::vector<int32_t>& tri,
       const std::vector<float>& norm,
       const std::vector<float>& uv)
      : vertices(vert), triangles(tri), normals(norm), uvs(uv) {}

  std::vector<float> vertices;
  std::vector<int32_t> triangles;
  std::vector<float> normals;
  std::vector<float> uvs;

  static Mesh FromFile(const std::string& path);
};