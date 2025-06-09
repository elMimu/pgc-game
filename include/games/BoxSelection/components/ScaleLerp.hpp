#pragma once

#include "games/BoxSelection/components/FloatOut.hpp"
#include "raylib.h"
#include <functional>

struct ScaleLerp {
  Vector2 to;
  float speed = 1.0f;
  std::function<void()> callback = []() {};
  float (*easing)(float) = Easing::easeLinear;
  Vector2 from;
  float progress = 0.0f;
};
