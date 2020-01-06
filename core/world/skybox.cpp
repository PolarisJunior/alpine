#include "skybox.h"

#include <SDL.h>
#include <SDL_image.h>
#include <gl/glew.h>
#include <algorithm>

#include "core/primitive.h"
#include "graphics/graphics_client.h"
#include "graphics/sized_mesh_buffers.h"

Skybox::Skybox(const std::array<std::string, 6>& face_files) {
  glGenTextures(1, &cube_map_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id);

  for (int i = 0; i < 6; i++) {
    int32_t format = GL_RGB;

    SDL_Surface* surf = IMG_Load(face_files[i].c_str());
    int32_t num_bytes = surf->pitch * surf->h;
    SDL_LockSurface(surf);
    if (SDL_ISPIXELFORMAT_ALPHA(surf->format->format)) {
      format = GL_RGBA;
    }
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, surf->w,
                 surf->h, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

    SDL_UnlockSurface(surf);
    SDL_FreeSurface(surf);
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::Render() {
  glFrontFace(GL_CCW);
  glDepthFunc(GL_LEQUAL);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id);
  SizedMeshBuffers buffers = GraphicsClient::SendMesh(Primitive::cube_mesh);
  GraphicsClient::Draw(buffers);
  GraphicsClient::UnbindBuffers(buffers);
  glFrontFace(GL_CW);
  glDepthFunc(GL_LESS);
}