#pragma once

class Rasterizer {
 public:
  static void SetClearColor(float r, float g, float b, float a);
  static void Clear();

  static void Rasterize();
  static void SwapWindow();
};