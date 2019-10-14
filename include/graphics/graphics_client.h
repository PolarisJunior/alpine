#pragma once

#include "sized_mesh_buffers.h"

class Mesh;

class GraphicsClient {
 public:
  static SizedMeshBuffers SendMesh(const Mesh& mesh);

  static void UnbindBuffers(MeshBuffers& buffers);
  static void Draw(const SizedMeshBuffers& buffers);
};