#pragma once
#include "raylib.h"
#include <cstdint>

struct RenderRectangle
{
  std::uint32_t layer;
  Color color;
  RenderRectangle(std::uint32_t layer, Vector4 color)
      : layer(layer), color(ColorFromNormalized(color)) {};
  RenderRectangle(std::uint32_t layer, Color color)
      : layer(layer), color(color) {};
};
