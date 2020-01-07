#include "program.h"

#include <SDL.h>

#include "drivers/drivers.h"

#include "drivers/peripherals/keyboard.h"
#include "ui/window.h"
#include "ui/window_builder.h"

#include <iostream>
#include "event_broadcaster.h"

void Program::Init() {
  Drivers::Init();

  WindowBuilder window_builder;
  window_builder.Title(Program::program_title);
  Program::main_window = window_builder.Build();

  Drivers::InitGraphics(*main_window);

  EventBroadcaster::AddListener(Event::QUIT, []() { Program::Stop(); });

  Keyboard::Initialize();
}

Window& Program::GetMainWindow() {
  return *Program::main_window;
}

uint32_t Program::GetTicks() {
  return SDL_GetTicks();
}

real_t Program::GetSeconds() {
  return static_cast<real_t>(GetTicks()) / 1000.0;
}