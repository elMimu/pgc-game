#pragma once

#include "engine/core/Types.hpp"
#include "raylib.h"
#include <functional>
#include <queue>

struct ItemBoxCounter {
  std::queue<Entity> items;
  float delay;
  float timeElapsed;
  Color countColor;
  std::function<void()> onCount;
  std::function<void()> onFinish;
  int count = 0;
  bool start = false;
  bool loaded = false;

  ItemBoxCounter(
      float delay, Color countColor = WHITE, std::queue<Entity> items = {},
      std::function<void()> onCount = []() {},
      std::function<void()> onFinish = []() {})
      : delay(delay), countColor(countColor), timeElapsed(0.0f), items(items),
        onCount(onCount), onFinish(onFinish) {}
};
