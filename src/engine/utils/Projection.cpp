#include "engine/utils/Projection.hpp"
#include "raylib.h"

namespace Projection
{
static Matrix projection = MatrixIdentity();
static int lastWidth = 0;
static int lastHeight = 0;

void update()
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  if (width != lastWidth || height != lastHeight)
  {
    projection = MatrixOrtho(0, width, height, 0, 0, 1);

    lastWidth = width;
    lastHeight = height;
  }
}

Matrix get()
{
  return projection;
}
} // namespace Projection
