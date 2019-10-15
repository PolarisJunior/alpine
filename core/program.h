#pragma once

#include <string>
#include "ui/window.h"

class Program {
  inline static Window main_window;

 public:
  inline static const std::string PROGRAM_TITLE = "Alpine Engine";

  static void Init();

  static Window& GetMainWindow();
};