#pragma once

#include <functional>
#include <map>

enum class Event : uint32_t { QUIT = 0x100, KEY_DOWN = 0x300, KEY_UP };

class EventBroadcaster {
  inline static std::map<Event, std::function<void(void)>> listeners;

 public:
  // static void NotifyAll();

  static void AddListener(Event event, std::function<void(void)> listener);
  static void PollEvents();
};