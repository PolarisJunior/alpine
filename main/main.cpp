
#include <iostream>

#include "core/program.h"
#include "core/sys.h"

#include "core/event_broadcaster.h"

#include "drivers/drivers.h"
#include "drivers/rasterizer.h"

#include "drivers/peripherals/mouse.h"

#include "math/vector3.h"
#include "ui/window_builder.h"

int main(int argc, char* argv[]) {
  using namespace std;

  Program::Init();

  Rasterizer::SetClearColor(0.0, 0.1, 0.3, 1.0);
  Rasterizer::Clear();
  Rasterizer::Rasterize();

  while (!Program::IsStopping()) {
    Mouse::Repoll();
    EventBroadcaster::PollEvents();
  }

  exit(EXIT_SUCCESS);
}