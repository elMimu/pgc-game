#pragma once
#include "engine/components/Visual.hpp"
#include "raylib.h"
#include "rlgl.h"

namespace Basic2DShader
{
void draw(const Matrix &projection, const Matrix &transform,
          const Visual &r); // load shader from disk
} // namespace Basic2DShader
