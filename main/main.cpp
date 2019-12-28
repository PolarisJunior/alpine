
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

#include <gl/glew.h>

int main(int argc, char* argv[]) {
  std::cout << "Starting Alpine Engine...\n";
  Program::Init();

  QuadMesh mesh{};
  ShaderProgramBuilder program_builder{};
  program_builder.AddVertFromFile("resources/shaders/flat.vert");
  program_builder.AddFragFromFile("resources/shaders/flat.frag");
  auto shader_program = program_builder.Build();

  while (!Program::IsStopRequested()) {
    Mouse::Repoll();
    EventBroadcaster::PollEvents();

    Rasterizer::SetClearColor(0.0, 0.25,
                              Math::Abs(Math::Cos(Program::GetSeconds())), 1.0);
    Rasterizer::Clear();

    shader_program->Use();
    MeshBuffers buffers = GraphicsClient::SendMesh(mesh);

    glBindVertexArray(buffers.vao);
    glDrawElements(GL_TRIANGLES, mesh.triangles.size(), GL_UNSIGNED_INT, 0);
    Rasterizer::SwapWindow();

    GraphicsClient::UnbindBuffers(buffers);
  }

  exit(EXIT_SUCCESS);
}