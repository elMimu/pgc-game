#include "raylib.h"
struct InputState
{
  Vector2 pointerPos = {0.0f, 0.0f};
  bool pointerDown = false;
  bool pointerReleased = false;
};
