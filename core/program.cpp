#include "program.h"

#include "drivers/drivers.h"
#include "ui/window.h"
#include "ui/window_builder.h"

#include "event_broadcaster.h"

void Program::Init() {
  Drivers::Init();

  WindowBuilder window_builder;
  window_builder.Title(Program::PROGRAM_TITLE);
  Program::main_window = window_builder.Build();

  Drivers::InitGraphics(main_window);

  EventBroadcaster::AddListener(Event::QUIT, []() { Program::Stop(); });
}

Window& Program::GetMainWindow() {
  return Program::main_window;
}