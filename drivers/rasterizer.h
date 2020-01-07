#pragma once

#include "core/loop_registry.h"

class Rasterizer : LoopRegistry::Preloop<Rasterizer> {
 public:
  static void SetClearColor(float r, float g, float b, float a);
  static void Clear();

  static void Rasterize();
  static void SwapWindow();

  static void Update();
};