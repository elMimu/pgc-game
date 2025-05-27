#pragma once
#include "raylib.h"
#include "raymath.h"

struct GlobalTransformable
{
  Matrix worldMatrix = MatrixIdentity();
  bool dirty = true;
};
