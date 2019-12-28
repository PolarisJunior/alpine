#include "mesh_buffers.h"

struct SizedMeshBuffers : public MeshBuffers {
  int32_t num_elements;
};