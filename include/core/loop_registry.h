#pragma once

#include <functional>
#include <iostream>

class LoopRegistry {
  static void AddToRegistry(std::function<void(void)> f) {
    LoopRegistry::update_funcs.push_back(f);
  }

  inline static std::vector<std::function<void(void)>> update_funcs;

 public:
  inline static void UpdateAll() {
    for (auto f : update_funcs) {
      f();
    }
  }

  template <typename T>
  class Preloop {
   public:
    static bool AddToUpdateList() {
      AddToRegistry(T::Update);
      return true;
    }

   private:
    inline static bool b = AddToUpdateList();
  };
};
