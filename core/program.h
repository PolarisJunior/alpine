#pragma once

#include <string>
#include "ui/window.h"

class Program {
  inline static Window main_window;
  inline static bool stop_requested = false;

 public:
  inline static const std::string PROGRAM_TITLE = "Alpine Engine";

  static void Init();

  static void Stop() { stop_requested = true; }
  static bool IsStopping() { return stop_requested; }

  static Window& GetMainWindow();
};