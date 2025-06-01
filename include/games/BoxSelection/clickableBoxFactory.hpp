#pragma once

#include "engine/components/Clickable.hpp"
#include "engine/core/Types.hpp"
#include "games/BoxSelection/itemBoxFactory.hpp"

class ClickableBoxFactory
{
public:
  static Entity creatClickableBox(World &world, int quantity, Vector2 origin,
                                  Vector2 position, Vector2 size,
                                  float rotation, uint32_t priority,
                                  Color boxColor, Color itemColor)
  {
    Entity box =
        itemBoxFactory::createItemBox(world, quantity, origin, position, size,
                                      rotation, priority, boxColor, itemColor);
    setupSystem(world, box);
    return box;
  }

  static void setupSystem(World &world, Entity e)
  {
    world.attach<Clickable>(
        e, Clickable([](Entity e) { std::cout << "on click\n"; },
                     [](Entity e) { std::cout << "on release\n"; }));
  }
};
