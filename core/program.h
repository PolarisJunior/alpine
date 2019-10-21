#pragma once

#include <string>

#include "math/math_defs.h"
#include "ui/window.h"

class Program {
  inline static Window main_window;
  inline static bool stop_requested = false;

 public:
  inline static const std::string PROGRAM_TITLE = "Alpine Engine";

  static void Init();

  static void Stop() { stop_requested = true; }
  static bool IsStopRequested() { return stop_requested; }

  static uint32_t GetTicks();
  static real_t GetSeconds();

  static Window& GetMainWindow();
};