
#pragma once

#include <array>
#include <cstdint>

#include "core/loop_registry.h"

class Mouse : LoopRegistry::Preloop<Mouse> {
  static constexpr uint8_t NUM_BUTTONS = 3;

  struct MouseState {
    int32_t x = 0xDEADBEEF;
    int32_t y = 0xDEADBEEF;

    std::array<bool, NUM_BUTTONS> pressed;
    std::array<bool, NUM_BUTTONS> down_this_frame;
    std::array<bool, NUM_BUTTONS> up_this_frame;

    /* Due to a bug in GCC this line is required */
    MouseState(){};
  };

  inline static MouseState state = {};
  static std::array<uint8_t, NUM_BUTTONS> button_masks;

 public:
  static bool Right();
  static bool Left();
  static bool Middle();

  static bool GetButton(uint32_t button);
  static bool GetButtonDown(uint32_t button);
  static bool GetButtonUp(uint32_t button);

  static int32_t GetX();
  static int32_t GetY();

  static void Repoll();
  static void Update();
};