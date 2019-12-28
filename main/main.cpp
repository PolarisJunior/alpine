
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

#include "core/meshes/cube_mesh.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  CubeMesh mesh{};
  ShaderProgramBuilder program_builder{};
  program_builder.AddVertFromFile("resources/shaders/sine.vert");
  program_builder.AddFragFromFile("resources/shaders/sine.frag");
  auto shader_program = program_builder.Build();

  while (!Program::IsStopRequested()) {
    Mouse::Repoll();
    EventBroadcaster::PollEvents();

    Rasterizer::SetClearColor(0.0, 0.25,
                              Math::Abs(Math::Cos(Program::GetSeconds())), 1.0);
    Rasterizer::Clear();

    shader_program->Use();
    shader_program->SetUniform("u_time", Program::GetSeconds());

    SizedMeshBuffers buffers = GraphicsClient::SendMesh(mesh);
    GraphicsClient::Draw(buffers);

    Rasterizer::SwapWindow();

    GraphicsClient::UnbindBuffers(buffers);
  }

  exit(EXIT_SUCCESS);
}