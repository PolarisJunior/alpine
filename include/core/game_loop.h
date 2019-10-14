#pragma once
#include <entt/entt.hpp>

class GameLoop {
 public:
  double last_render_time;
  double last_update_time;

  virtual void HandleInput();
  virtual void Update(entt::registry& registry);
  virtual void Render();
  virtual void Next();

  virtual void Run();
};