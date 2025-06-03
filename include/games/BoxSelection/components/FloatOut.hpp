#pragma once
#include "engine/utils/Easing.hpp"
#include "raylib.h"

struct FloatOut {
  Vector2 startPos;
  Vector2 endPos;
  Vector2 startScale;
  Vector2 endScale;
  float speed = 1.0f;
  float (*easing)(float) = Easing::easeInQuad;
  float progress = 0.0f;
  float loaded = false;
  float play = false;

  FloatOut(Vector2 startPos, Vector2 endPos, Vector2 startScale,
           Vector2 endScale)
      : startPos(startPos), endPos(endPos), startScale(startScale),
        endScale(endScale) {}
  FloatOut(Vector2 startPos, Vector2 endPos, Vector2 startScale,
           Vector2 endScale, float speed, float (*easing)(float))
      : startPos(startPos), endPos(endPos), startScale(startScale),
        endScale(endScale), speed(speed), easing(easing) {}
};
