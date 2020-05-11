#pragma once

#include <memory>
#include <string>

#include "pjmath/math_defs.hpp"
#include "ui/window.h"

class Program {
  inline static std::unique_ptr<Window> main_window;
  inline static bool stop_requested = false;

 public:
  inline static const std::string program_title = "Alpine Engine";

  static void Init();

  static void Stop() { stop_requested = true; }
  static bool IsStopRequested() { return stop_requested; }

  static uint32_t GetTicks();
  static real_t GetSeconds();

  static Window& GetMainWindow();
};
