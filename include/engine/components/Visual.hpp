#pragma once

#include "raylib.h"
#include <cstdint>

struct Visual {
  Color color = WHITE;
  uint32_t layer = 0;

  Visual(Color color = WHITE, uint32_t layer = 0)
      : color(color), layer(layer) {}
  Visual(Vector4 color, uint32_t layer = 0)
      : color(ColorFromNormalized(color)), layer(layer) {}
};
