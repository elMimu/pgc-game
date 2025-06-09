#pragma once

#include "raylib.h"
#include <string>

struct RenderText {
  std::string text;
  Font font = GetFontDefault();
  bool dirty = true;
  float baseWidth = 0.0f;

  RenderText(std::string text, Font font = GetFontDefault())
      : text(text), font(font) {};
};
