#pragma once

#include "games/BoxSelection/components/FloatOut.hpp"
#include "raylib.h"
#include <functional>

struct ScaleAnimation {
  Vector2 startScale;
  Vector2 endScale;
  float speed = 1;
  std::function<void()> callback;
  float (*easing)(float);
  float progress = 0;
  bool play = false;

  ScaleAnimation(
      Vector2 startScale, Vector2 endScale, float speed,
      std::function<void()> callback = []() {},
      float (*easing)(float) = Easing::easeInQuad)
      : startScale(startScale), endScale(endScale), speed(speed),
        callback(callback) {}
};
