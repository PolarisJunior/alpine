#include "graphics_client.h"

#include <gl/glew.h>
#include <array>

#include "core/meshes/mesh.h"

void GraphicsClient::Draw(const SizedMeshBuffers& buffers) {
  glBindVertexArray(buffers.vao);
  glDrawElements(GL_TRIANGLES, buffers.num_elements, GL_UNSIGNED_INT, 0);
}

SizedMeshBuffers GraphicsClient::SendMesh(const Mesh& mesh) {
  SizedMeshBuffers buffers{};

  glGenVertexArrays(1, &buffers.vao);

  glGenBuffers(4, buffers.buffers.data());

  glBindVertexArray(buffers.vao);

  // UVS
  glBindBuffer(GL_ARRAY_BUFFER, buffers.uv);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * mesh.uvs.size(),
               mesh.uvs.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(1);

  // NORMALS
  glBindBuffer(GL_ARRAY_BUFFER, buffers.norms);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.normals.size(),
               mesh.normals.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(2);

  // POSITIONS
  glBindBuffer(GL_ARRAY_BUFFER, buffers.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * mesh.vertices.size(),
               mesh.vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // INDICES/TRIANGLES
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int32_t) * mesh.triangles.size(),
               mesh.triangles.data(), GL_STATIC_DRAW);

  // UNBIND
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  buffers.num_elements = mesh.triangles.size();
  return buffers;
}

void GraphicsClient::UnbindBuffers(MeshBuffers& buffers) {
  glDeleteVertexArrays(1, &buffers.vao);
  glDeleteBuffers(buffers.buffers.size(), buffers.buffers.data());
}
