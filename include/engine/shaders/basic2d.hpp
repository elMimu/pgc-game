#pragma once
#include "engine/components/RenderRectangle.hpp"
#include "raylib.h"
#include "rlgl.h"

namespace Basic2DShader
{
void draw(const Matrix &projection, const Matrix &transform,
          const RenderRectangle &r); // load shader from disk
} // namespace Basic2DShader
