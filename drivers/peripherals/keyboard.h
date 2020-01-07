
#pragma once

#include <cstdint>
#include "core/loop_registry.h"

class Keyboard : LoopRegistry::Preloop<Keyboard> {
  static constexpr int32_t NUM_SCANCODES = 512;

  inline static bool initialized = false;

  static const uint8_t* key_states;

 public:
  static void Initialize();

  static bool KeyDown(uint32_t scan_code);

  enum ScanCode { A = 4 };

  static void Update();
};