
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

#include "core/meshes/quad_mesh.h"

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  QuadMesh mesh{};
  ShaderProgramBuilder program_builder{};
  auto shader_program = program_builder.build();
  while (!Program::IsStopRequested()) {
    Mouse::Repoll();
    EventBroadcaster::PollEvents();

    Rasterizer::SetClearColor(0.0, 0.1,
                              Math::Abs(Math::Cos(Program::GetSeconds())), 1.0);
    Rasterizer::Clear();

    shader_program->Use();
    MeshBuffers buffers = GraphicsClient::SendMesh(mesh);
    GraphicsClient::UnbindBuffers(buffers);

    Rasterizer::SwapWindow();
  }

  exit(EXIT_SUCCESS);
}