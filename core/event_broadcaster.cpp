#include "event_broadcaster.h"

#include <SDL.h>

void EventBroadcaster::AddListener(Event event,
                                   std::function<void(void)> listener) {
  listeners[event] = listener;
}

void EventBroadcaster::PollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    auto it = listeners.find(static_cast<Event>(event.type));
    if (it != listeners.end()) {
      it->second();
    }
  }
}