#include "core/world/skybox.h"

#include <SDL.h>
#include <SDL_image.h>
#include <gl/glew.h>
#include <algorithm>

#include "core/camera.h"
#include "core/primitive.h"
#include "graphics/graphics_client.h"
#include "graphics/shader_program.h"
#include "graphics/shader_program_builder.h"
#include "graphics/sized_mesh_buffers.h"

static std::array<std::string, 6> DefaultFaceFiles() {
  std::array<std::string, 6> skybox_faces = {"right",  "left",  "top",
                                             "bottom", "front", "back"};
  std::transform(
      skybox_faces.begin(), skybox_faces.end(), skybox_faces.begin(),
      [](const auto& str) { return "resources/skybox/" + str + ".jpg"; });
  return skybox_faces;
}

static std::unique_ptr<ShaderProgram> DefaultShaderProgram() {
  ShaderProgramBuilder skybox_program_builder{};
  skybox_program_builder.AddVertFromFile("resources/shaders/skybox.vert");
  skybox_program_builder.AddFragFromFile("resources/shaders/skybox.frag");
  auto skybox_shader_program = skybox_program_builder.Build();
  return skybox_shader_program;
}

Skybox::Skybox() : Skybox(DefaultFaceFiles(), DefaultShaderProgram()) {}

Skybox::Skybox(const std::array<std::string, 6>& face_files,
               std::unique_ptr<ShaderProgram> prog)
    : shader_program(std::move(prog)) {
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

void Skybox::Render(const Camera& camera) {
  shader_program->Use();
  shader_program->SetUniform("view", camera.ViewMatrix());
  shader_program->SetUniform("projection", camera.ProjectionMatrix());

  glFrontFace(GL_CCW);
  glDepthFunc(GL_LEQUAL);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_id);
  SizedMeshBuffers buffers = GraphicsClient::SendMesh(Primitive::cube_mesh);
  GraphicsClient::Draw(buffers);
  GraphicsClient::UnbindBuffers(buffers);
  glFrontFace(GL_CW);
  glDepthFunc(GL_LESS);
}
