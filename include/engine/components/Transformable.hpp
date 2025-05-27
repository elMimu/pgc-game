#pragma once
#include "raylib.h"
#include <cstdint>

struct Transformable
{
  Vector2 origin;
  Vector2 position;
  Vector2 size;
  float rotation;
  uint32_t parent;
  Transformable(Vector2 origin, Vector2 position, Vector2 size, float rotation,
                uint32_t parent = 0)
      : origin(origin), position(position), size(size), rotation(rotation),
        parent(parent)
  {
  }
};
