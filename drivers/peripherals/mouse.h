
#pragma once

#include <array>
#include <cstdint>

class Mouse {
  static constexpr uint8_t NUM_BUTTONS = 3;

  struct MouseState {
    int32_t x = 0xDEADBEEF;
    int32_t y = 0xDEADBEEF;

    std::array<bool, NUM_BUTTONS> pressed;
    std::array<bool, NUM_BUTTONS> down_this_frame;
    std::array<bool, NUM_BUTTONS> up_this_frame;
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
};