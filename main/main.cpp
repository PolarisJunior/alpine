
#include <iostream>
#include "math/vector3.h"
#include "test/foo.h"

int main(int argc, char** argv) {
  using namespace std;
  Vector3 v = Vector3::one;
  cout << "Hello Alpine" << v.x << endl;

  exit(EXIT_FAILURE);
}