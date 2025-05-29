#pragma once
#include "engine/components/Transformable.hpp"
#include "engine/core/World.hpp"
#include "raylib.h"

namespace TransformUtils
{
struct WorldMatrixResult
{
  Matrix &matrix;
  bool changed;
};
Matrix getLocalMatrix(const Transformable &t);
float getAspect(Entity e, World &w);
WorldMatrixResult getSafeWorldMatrix(World &w, Entity e, Transformable &t);
Matrix &getWorldMatrix(World &w, Entity e, Transformable &t);
} // namespace TransformUtils
