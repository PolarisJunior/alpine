#include "core/game_loop.h"

#include <entt/entt.hpp>

#include "core/camera.h"
#include "core/event_broadcaster.h"
#include "core/game_loop.h"
#include "core/primitive.h"
#include "core/program.h"
#include "drivers/drivers.h"
#include "drivers/peripherals/mouse.h"
#include "drivers/rasterizer.h"
#include "graphics/graphics_client.h"
#include "graphics/shader_program.h"
#include "graphics/shader_program_builder.h"
#include "math/mat4.h"
#include "math/vector3.h"
#include "pjmath/math_funcs.hpp"
#include "ui/window_builder.h"

void GameLoop::HandleInput() {
  Mouse::Repoll();
  EventBroadcaster::PollEvents();
}

void GameLoop::Update(entt::registry& registry) {}

void GameLoop::Render() {
  Rasterizer::SwapWindow();
}

void GameLoop::Next() {
  this->HandleInput();
  // this->Update();
  this->Render();
}

void GameLoop::Run() {
  while (!Program::IsStopRequested()) {
    this->Next();
  }
}
