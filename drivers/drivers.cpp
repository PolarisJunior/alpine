
#include "drivers.h"

// Required to use static linkage with GLEW
#define GLEW_STATIC
#include <gl/glew.h>

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <string>

#include "ui/window.h"

void Drivers::Init() {
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
}

void Drivers::InitGraphics(Window& window) {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_GLContext context =
      SDL_GL_CreateContext(static_cast<SDL_Window*>(window.raw_window));

  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << std::string(reinterpret_cast<const char*>(
                     (glewGetErrorString(glewError))))
              << std::endl;
    exit(EXIT_FAILURE);
  }

  if (SDL_GL_SetSwapInterval(1) < 0) {
    std::cout << std::string(SDL_GetError()) << std::endl;
    exit(EXIT_FAILURE);
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CW);
#ifdef ALPINE_3D
  glEnable(GL_MULTISAMPLE);
#endif
#ifdef ALPINE_2D

#endif
}
