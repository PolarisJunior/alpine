
#include "keyboard.h"

#include <SDL.h>
#include <iostream>

const uint8_t* Keyboard::key_states;

static void RunUpdateLoop() {}

void Keyboard::Initialize() {
  key_states = SDL_GetKeyboardState(nullptr);
}

bool Keyboard::KeyDown(uint32_t scan_code) {
  return key_states[scan_code];
}

bool Keyboard::KeyDown(ScanCode scan_code) {
  return KeyDown(static_cast<uint32_t>(scan_code));
}

void Keyboard::Update() {}