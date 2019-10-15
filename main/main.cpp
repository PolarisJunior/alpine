
#include <SDL.h>
#include <iostream>

#include "core/sys.h"
#include "math/vector3.h"
#include "ui/window_builder.h"

int main(int argc, char* argv[]) {
  using namespace std;
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
  WindowBuilder window_builder;
  window_builder.Title("Alpine Engine");
  Window window = window_builder.Build();

  Sys::Delay(1);

  Vector3 v = Vector3::zero;
  cout << "Hello Alpine" << v.x << endl;

  exit(EXIT_SUCCESS);
}