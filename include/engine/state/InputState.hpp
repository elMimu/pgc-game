#include "engine/components/Transformable.hpp"
#include "raylib.h"
struct InputState
{
  Vector2 pointerPos;
  bool pointerDown;
  bool pointerReleased;

  static bool pointInside(Vector2 pos, const Transformable &t)
  {
    return pos.x >= t.position.x && pos.x <= t.position.x + t.size.x &&
           pos.y >= t.position.y && pos.y <= t.position.y + t.size.y;
  }
};
