#pragma once

#include "ui/window.h"

class Drivers {
 public:
  static void Init();

  static void InitGraphics(Window& window);

 private:
  static void EnableVSync();
  static void SetGlAttributes();
};
