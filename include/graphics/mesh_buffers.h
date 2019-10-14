
#pragma once

#include <array>
#include <cstdint>

struct MeshBuffers {
  uint32_t vao;
  union {
    struct {
      uint32_t vbo;
      uint32_t ebo;
      uint32_t uv;
      uint32_t norms;
    };

    std::array<uint32_t, 4> buffers;
  };
};