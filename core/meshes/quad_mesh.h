#pragma once
#include "Mesh.h"

class QuadMesh : public Mesh {
 public:
  QuadMesh() : Mesh(quad_vertices, quad_triangles, quad_normals, quad_uvs) {}

  inline static const std::vector<float> quad_vertices = {
      -.5, 0, .5, .5, 0, .5, -.5, 0, -.5, .5, 0, -.5,
      -.5, 0, .5, .5, 0, .5, -.5, 0, -.5, .5, 0, -.5};

  inline static const std::vector<int32_t> quad_triangles = {0, 1, 2, 1, 3, 2,
                                                             6, 5, 4, 6, 7, 5};

  inline static const std::vector<float> quad_uvs = {1, 0, 0, 0, 1, 1, 0, 1,
                                                     1, 0, 0, 0, 1, 1, 0, 1};
  inline static const std::vector<float> quad_normals = {
      0, 1,  0, 0, 1,  0, 0, 1,  0, 0, 1,  0,
      0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0};
};