
#include <iostream>

#include "core/program.h"
#include "core/sys.h"

#include "drivers/drivers.h"
#include "math/vector3.h"
#include "ui/window_builder.h"

int main(int argc, char* argv[]) {
  using namespace std;

  Program::Init();

  Sys::Delay(1);

  cout << "Hello Alpine" << endl;

  exit(EXIT_SUCCESS);
}