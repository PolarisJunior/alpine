#include "drivers/peripherals/mouse.h"

#include <SDL.h>

std::array<uint8_t, Mouse::NUM_BUTTONS> Mouse::button_masks = {
    SDL_BUTTON_LEFT, SDL_BUTTON_RIGHT, SDL_BUTTON_MIDDLE};

bool Mouse::Left() {
  return state.pressed[0];
}

bool Mouse::Right() {
  return state.pressed[1];
}

bool Mouse::Middle() {
  return state.pressed[2];
}

bool Mouse::GetButton(uint32_t button) {
  return state.pressed[button];
}
bool Mouse::GetButtonDown(uint32_t button) {
  return state.down_this_frame[button];
}

bool Mouse::GetButtonUp(uint32_t button) {
  return state.up_this_frame[button];
}

int32_t Mouse::GetX() {
  return state.x;
}

int32_t Mouse::GetY() {
  return state.y;
}

void Mouse::Repoll() {
  uint32_t pressed_buttons = SDL_GetMouseState(&state.x, &state.y);

  for (int i = 0; i < button_masks.size(); i++) {
    uint8_t mask = button_masks[i];
    state.down_this_frame[i] = false;
    state.up_this_frame[i] = false;

    bool prev_pressed = state.pressed[i];
    state.pressed[i] = pressed_buttons & mask;
    if (state.pressed[i] && !prev_pressed) {
      state.down_this_frame[i] = true;
    } else if (!state.pressed[i] && prev_pressed) {
      state.up_this_frame[i] = true;
    }
  }
}

void Mouse::Update() {
  Repoll();
}