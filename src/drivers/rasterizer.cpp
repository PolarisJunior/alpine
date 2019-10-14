#include "drivers/rasterizer.h"

#include "core/program.h"

#include <GL/glew.h>
#include <SDL.h>

void Rasterizer::SetClearColor(float r, float g, float b, float a) {
  glClearColor(r, g, b, a);
}

void Rasterizer::Clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Rasterizer::SwapWindow() {
  Program::GetMainWindow().SwapWindow();
}

void Rasterizer::Update() {
  Rasterizer::SetClearColor(0.0, 0.0, 0.0, 1.0);
  Rasterizer::Clear();
}
