#pragma once

#include "engine/core/Types.hpp"
#include "engine/core/World.hpp"
#include "raylib.h"

class itemBoxFactory
{
public:
  static Entity createItemBox(World &world, int quantity, Vector2 origin,
                              Vector2 position, Vector2 size, float rotation,
                              uint32_t priority, Color boxColor,
                              Color itemColor);

private:
  static void createItems(World &world, int quantity, Entity parent,
                          Color color);

  static Entity createBox(World &world, Vector2 origin, Vector2 position,
                          Vector2 size, float rotation, uint32_t priority,
                          Color boxColor);

  static Entity createBoxItem(World &world, Vector2 position, Entity parent,
                              Color color, float aspect, float maxWidth,
                              float maxHeight);

  static std::vector<Vector2> mapItemsPosition(int items, float w, float h);

  static std::vector<Vector2> mapEvenItemsPosition(int items, float w, float h);

  static std::vector<Vector2> mapOddItemsPosition(int items, float w, float h);
};
