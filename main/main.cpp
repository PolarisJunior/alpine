
#include <iostream>

#include <algorithm>
#include <entt/entt.hpp>

#include "core/program.h"
#include "core/sys.h"

#include "core/event_broadcaster.h"

#include "graphics/graphics_client.h"
#include "graphics/shader_program.h"

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
#include "graphics/material.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  Skybox skybox{};

  Camera camera;
  camera.transform.Translate(Vector3(1.0, 0.0, -3.0));
  camera.transform.Rotate(PI / 2, Vector3::forward);

  entt::registry registry;
  auto entity = registry.create();
  registry.assign<Transform>(entity, Transform{1.0, 0.0, 0.0});
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  Material& mat = registry.assign<Material>(
      entity, "resources/shaders/simple.vert", "resources/shaders/simple.frag");
  entity = registry.create();
  registry.assign<Transform>(entity);
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  registry.get<Transform>(entity).Rotate(PI / 2, Vector3(0.5, 0.5, 0));
  registry.assign<Material>(entity, Material{mat});

  while (!Program::IsStopRequested()) {
    LoopRegistry::UpdateAll();

    skybox.Render(camera);

    auto view = registry.view<Transform, Mesh, Material>();
    for (auto entity : view) {
      Transform& t = view.get<Transform>(entity);
      Material& mat = view.get<Material>(entity);
      Mesh& mesh = view.get<Mesh>(entity);
      mat.shader->Use();
      mat.shader->SetUniform("u_time", Program::GetSeconds());
      mat.shader->SetUniform("PV", camera.ProjectionViewMatrix());
      mat.shader->SetUniform("model", t.ModelMatrix());
      mat.shader->SetUniform("model_normal", t.ModelMatrix());

      SizedMeshBuffers buffers = GraphicsClient::SendMesh(mesh);
      GraphicsClient::Draw(buffers);
      GraphicsClient::UnbindBuffers(buffers);
    }

    Rasterizer::SwapWindow();
  }

  exit(EXIT_SUCCESS);
}