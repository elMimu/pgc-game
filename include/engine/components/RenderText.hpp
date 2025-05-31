#pragma once

#include "raylib.h"
#include <cstdint>
#include <string>

struct RenderText
{
  std::string text;
  Font font = GetFontDefault();
  Color color = BLACK;
  uint32_t priority = 0;
  bool dirty = true;
  float baseWidth = 0.0f;

  RenderText(std::string text, Font font, Color color, uint32_t priority)
      : text(text), font(font), color(color), priority(priority) {};

  RenderText(std::string text, Font font, Vector4 color, uint32_t priority)
      : text(text), font(font), priority(priority),
        color(ColorFromNormalized(color)) {};
};
