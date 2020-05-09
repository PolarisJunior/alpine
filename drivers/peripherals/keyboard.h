
#pragma once

#include <cstdint>
#include "core/loop_registry.h"

class Keyboard : LoopRegistry::Preloop<Keyboard> {
  static constexpr int32_t NUM_SCANCODES = 512;

  inline static bool initialized = false;

  static const uint8_t* key_states;

 public:
  enum class ScanCode {
    A = 4,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    RIGHT = 79,
    LEFT,
    DOWN,
    UP
  };

  static void Initialize();

  static bool KeyDown(uint32_t scan_code);
  static bool KeyDown(ScanCode scan_code);

  static void Update();
};