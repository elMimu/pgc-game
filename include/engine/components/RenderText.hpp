#pragma once
#include "engine/core/Types.hpp"
#include "raylib.h"
#include <cstdint>
#include <string>

struct RenderText
{
  std::string text;
  int fontSize = 16;
  float spacing = 1.0f;
  Color color = BLACK;
  uint32_t priority = 0;
  Entity parent = 0;

  RenderText(std::string text, int fontSize, float spacing, Color color,
             uint32_t priority, Entity parent)
      : text(text), fontSize(fontSize), spacing(spacing), color(color),
        priority(priority), parent(parent) {};

  RenderText(std::string text, int fontSize, float spacing, Vector4 color,
             uint32_t priority, Entity parent)
      : text(text), fontSize(fontSize), spacing(spacing), priority(priority),
        color(ColorFromNormalized(color)) {};
};
