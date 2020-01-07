
#include <iostream>

#include <algorithm>
#include <entt/entt.hpp>

#include "core/program.h"
#include "core/sys.h"

#include "core/event_broadcaster.h"

#include "graphics/graphics_client.h"
#include "graphics/shader_program.h"
#include "graphics/shader_program_builder.h"

#include "drivers/drivers.h"
#include "drivers/rasterizer.h"

#include "drivers/peripherals/keyboard.h"
#include "drivers/peripherals/mouse.h"

#include "math/mat4.h"
#include "math/math_funcs.h"
#include "math/vector3.h"
#include "ui/window_builder.h"

#include "core/primitive.h"
#include "core/transform.h"

#include "core/camera.h"

#include "core/meshes/mesh.h"

#include "core/loop_registry.h"
#include "core/world/skybox.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  ShaderProgramBuilder program_builder{};
  program_builder.AddVertFromFile("resources/shaders/simple.vert");
  program_builder.AddFragFromFile("resources/shaders/simple.frag");
  auto shader_program = program_builder.Build();

  Skybox skybox{};

  Mat4 model = Mat4::Translate(1.0, 0.0, 0.0);
  model *= Mat4::Rotate(3.0, Vector3{.5, .5, 0.0});

  Camera camera;
  camera.transform.Translate(Vector3(1.0, 0.0, -3.0));
  camera.transform.Rotate(PI / 2, Vector3::forward);

  entt::registry registry;
  auto entity = registry.create();
  registry.assign<Transform>(entity, Transform{1.0, 0.0, 0.0});
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  entity = registry.create();
  registry.assign<Transform>(entity);
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  registry.get<Transform>(entity).Rotate(PI / 2, Vector3(0.5, 0.5, 0));

  while (!Program::IsStopRequested()) {
    LoopRegistry::UpdateAll();

    skybox.Render(camera);

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

    Rasterizer::SwapWindow();
  }

  exit(EXIT_SUCCESS);
}