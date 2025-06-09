#pragma once
#include "engine/utils/Easing.hpp"
#include "raylib.h"
#include <functional>

struct FloatOut {
  Vector2 startPos;
  Vector2 endPos;
  Vector2 startScale;
  Vector2 endScale;
  float speed = 1.0f;
  std::function<void()> callback;
  float (*easing)(float) = Easing::easeInQuad;
  float progress = 0.0f;
  float loaded = false;
  float play = false;

  FloatOut(
      Vector2 startPos, Vector2 endPos, Vector2 startScale, Vector2 endScale,
      std::function<void()> callback = []() {})
      : startPos(startPos), endPos(endPos), startScale(startScale),
        endScale(endScale), callback(callback) {}

  FloatOut(
      Vector2 startPos, Vector2 endPos, Vector2 startScale, Vector2 endScale,
      float speed, float (*easing)(float),
      std::function<void()> callback = []() {})
      : startPos(startPos), endPos(endPos), startScale(startScale),
        endScale(endScale), speed(speed), easing(easing), callback(callback) {}
};
