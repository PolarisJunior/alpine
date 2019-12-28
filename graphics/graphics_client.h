#pragma once

#include "mesh_buffers.h"

class Mesh;

class GraphicsClient {
 public:
  static MeshBuffers SendMesh(const Mesh& mesh);

  static void UnbindBuffers(MeshBuffers& buffers);
};