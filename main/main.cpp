
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

#include "core/game_loop.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  Skybox skybox{};

  Camera camera;
  camera.transform.Translate(Vector3(1.0, 0.0, -3.0));

  entt::registry registry;
  auto entity = registry.create();
  registry.assign<Transform>(entity, Transform{1.0, 0.0, 0.0});
  registry.assign<Mesh>(entity, Primitive::test_mesh);

  registry.assign<int*>(entity, nullptr);
  Material& mat = registry.assign<Material>(
      entity, "resources/shaders/simple.vert", "resources/shaders/simple.frag");
  entity = registry.create();
  registry.assign<Transform>(entity);
  registry.assign<Mesh>(entity, Primitive::cube_mesh);
  registry.get<Transform>(entity).Rotate(PI / 2, Vector3(0.5, 0.5, 0));
  registry.assign<Material>(entity, Material{mat});

  GameLoop loop;
  double last_update_time = Program::GetSeconds();
  constexpr real_t update_period = 1.0 / 60.0;

  while (!Program::IsStopRequested()) {
    LoopRegistry::UpdateAll();

    double delta = Program::GetSeconds() - last_update_time;
    if (delta >= update_period) {
      last_update_time = Program::GetSeconds();
      float speed = 10;
      if (Keyboard::KeyDown(Keyboard::ScanCode::W)) {
        camera.transform.Translate(Vector3::forward * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::S)) {
        camera.transform.Translate(Vector3::backward * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::A)) {
        camera.transform.Translate(Vector3::left * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::D)) {
        camera.transform.Translate(Vector3::right * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::J)) {
        camera.transform.Translate(Vector3::down * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::K)) {
        camera.transform.Translate(Vector3::up * delta * speed);
      }

      if (Keyboard::KeyDown(Keyboard::ScanCode::LEFT)) {
        camera.transform.Rotate(-0.5 * delta, Vector3::up);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::RIGHT)) {
        camera.transform.Rotate(0.5 * delta, Vector3::up);
      }
    }

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

    skybox.Render(camera);
    loop.Render();
  }

  exit(EXIT_SUCCESS);
}