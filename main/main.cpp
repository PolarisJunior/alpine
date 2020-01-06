
#include <iostream>

#include "core/program.h"
#include "core/sys.h"

#include "core/event_broadcaster.h"

#include "graphics/graphics_client.h"
#include "graphics/shader_program.h"
#include "graphics/shader_program_builder.h"

#include "drivers/drivers.h"
#include "drivers/rasterizer.h"

#include "drivers/peripherals/mouse.h"

#include "math/mat4.h"
#include "math/math_funcs.h"
#include "math/vector3.h"
#include "ui/window_builder.h"

#include "core/primitive.h"
#include "core/transform.h"

#include "core/camera.h"

#include "core/meshes/mesh.h"

#include <entt/entt.hpp>
#include "core/world/skybox.h"

#include <algorithm>

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  ShaderProgramBuilder program_builder{};
  program_builder.AddVertFromFile("resources/shaders/simple.vert");
  program_builder.AddFragFromFile("resources/shaders/simple.frag");
  auto shader_program = program_builder.Build();

  ShaderProgramBuilder skybox_program_builder{};
  skybox_program_builder.AddVertFromFile("resources/shaders/skybox.vert");
  skybox_program_builder.AddFragFromFile("resources/shaders/skybox.frag");
  auto skybox_shader_program = skybox_program_builder.Build();
  std::array<std::string, 6> skybox_faces = {"right",  "left",  "top",
                                             "bottom", "front", "back"};
  std::transform(
      skybox_faces.begin(), skybox_faces.end(), skybox_faces.begin(),
      [](const auto& str) { return "resources/skybox/" + str + ".jpg"; });
  Skybox skybox{skybox_faces};

  Mat4 model = Mat4::Translate(1.0, 0.0, 0.0);
  model *= Mat4::Rotate(3.0, Vector3{.5, .5, 0.0});

  Camera camera;
  camera.transform.Translate(Vector3(1.0, 0.0, -3.0));

  entt::registry registry;
  auto entity = registry.create();
  registry.assign<Transform>(entity, Transform{1.0, 0.0, 0.0});
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  entity = registry.create();
  registry.assign<Transform>(entity);
  registry.assign<Mesh>(entity, Primitive::cube_mesh);

  while (!Program::IsStopRequested()) {
    Mouse::Repoll();
    EventBroadcaster::PollEvents();

    Rasterizer::SetClearColor(0.0, 0.25,
                              Math::Abs(Math::Cos(Program::GetSeconds())), 1.0);
    Rasterizer::Clear();

    shader_program->Use();
    shader_program->SetUniform("u_time", Program::GetSeconds());
    shader_program->SetUniform("PV", camera.ProjectionViewMatrix());

    auto view = registry.view<Transform>();
    for (auto entity : view) {
      Transform& t = view.get(entity);
      shader_program->SetUniform("model", t.ModelMatrix());
      shader_program->SetUniform("model_normal", t.ModelMatrix());
      SizedMeshBuffers buffers = GraphicsClient::SendMesh(Primitive::cube_mesh);
      GraphicsClient::Draw(buffers);
      GraphicsClient::UnbindBuffers(buffers);
    }

    skybox_shader_program->Use();
    skybox_shader_program->SetUniform("view", camera.ViewMatrix());
    skybox_shader_program->SetUniform("projection", camera.ProjectionMatrix());
    skybox.Render();

    Rasterizer::SwapWindow();
  }

  exit(EXIT_SUCCESS);
}