
#include <algorithm>
#include <entt/entt.hpp>
#include <iostream>

#include "core/camera.h"
#include "core/event_broadcaster.h"
#include "core/game_loop.h"
#include "core/loop_registry.h"
#include "core/meshes/mesh.h"
#include "core/primitive.h"
#include "core/program.h"
#include "core/sys.h"
#include "core/transform.h"
#include "core/world/skybox.h"
#include "drivers/drivers.h"
#include "drivers/peripherals/keyboard.h"
#include "drivers/peripherals/mouse.h"
#include "drivers/rasterizer.h"
#include "graphics/graphics_client.h"
#include "graphics/material.h"
#include "graphics/shader_program.h"
#include "math/mat4.h"
#include "pjmath/math_funcs.hpp"
#include "pjmath/vector.hpp"
#include "ui/window_builder.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  Skybox skybox{};

  Camera camera;
  camera.transform.Translate(pjmath::Vector3{1.0, 0.0, -3.0});

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
  registry.get<Transform>(entity).Rotate(pjmath::PI / 2,
                                         pjmath::Vector3{0.5, 0.5, 0});
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
        camera.transform.Translate(pjmath::Vector3::Forward() * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::S)) {
        camera.transform.Translate(pjmath::Vector3::Backward() * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::A)) {
        camera.transform.Translate(pjmath::Vector3::Left() * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::D)) {
        camera.transform.Translate(pjmath::Vector3::Right() * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::J)) {
        camera.transform.Translate(pjmath::Vector3::Down() * delta * speed);
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::K)) {
        camera.transform.Translate(pjmath::Vector3::Up() * delta * speed);
      }

      if (Keyboard::KeyDown(Keyboard::ScanCode::LEFT)) {
        camera.transform.Rotate(-0.5 * delta, pjmath::Vector3::Up());
      }
      if (Keyboard::KeyDown(Keyboard::ScanCode::RIGHT)) {
        camera.transform.Rotate(0.5 * delta, pjmath::Vector3::Up());
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
