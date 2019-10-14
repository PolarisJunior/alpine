#pragma once

#include <functional>
#include <map>

#include "core/loop_registry.h"

enum class Event : uint32_t { QUIT = 0x100, KEY_DOWN = 0x300, KEY_UP };

class EventBroadcaster : LoopRegistry::Preloop<EventBroadcaster> {
  // inline static std::map<Event, std::function<void(void)>> listeners;
  inline static std::unordered_multimap<Event, std::function<void(void)>>
      listeners;

 public:
  static void AddListener(Event event, std::function<void(void)> listener);
  static void PollEvents();
  static void Update();
};