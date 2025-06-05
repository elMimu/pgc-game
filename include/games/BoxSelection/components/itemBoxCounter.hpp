#pragma once

#include "engine/core/Types.hpp"
#include <functional>
#include <queue>

struct ItemBoxCounter {
  std::queue<Entity> items;
  float delay;
  float timeElapsed;
  std::function<void()> callback;
  int count = 0;
  bool start = false;
  bool loaded = false;

  ItemBoxCounter(
      float delay, std::queue<Entity> items = {},
      std::function<void()> callback = []() {})
      : delay(delay), timeElapsed(delay) {}
};
