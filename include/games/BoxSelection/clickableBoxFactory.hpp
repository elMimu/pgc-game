#pragma once

#include "engine/components/Clickable.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/Types.hpp"
#include "games/BoxSelection/itemBoxFactory.hpp"
#include "raylib.h"
#include <cstdint>

class ClickableBoxFactory {
public:
  static Entity creatClickableBox(World &world, int quantity, Vector2 origin,
                                  Vector2 position, Vector2 size,
                                  float rotation, uint32_t priority,
                                  Color boxColor, Color itemColor) {
    Entity box =
        itemBoxFactory::createItemBox(world, quantity, origin, position, size,
                                      rotation, priority, boxColor, itemColor);

    Entity cover = createCover(world, box, priority);
    setupSystem(world, cover);
    return box;
  }

private:
  static Entity createCover(World &world, Entity parent, uint32_t priority) {
    Entity cover = world.entityManager.create();
    world.attach<Transformable>(
        cover,
        Transformable({0.5f, 0.5f}, {0.5f, 0.5f}, {1.0f, 1.0f}, 0.0f, parent));
    world.attach<GlobalTransformable>(cover, {});
    world.attach<RenderRectangle>(
        cover,
        {RenderRectangle(priority + 1, Vector4{0.0f, 0.0f, 0.0f, 0.0f})});
    return cover;
  }

  static void setupSystem(World &world, Entity e) {
    auto &rectRender = world.get<RenderRectangle>(e);
    world.attach<Clickable>(e, Clickable(
                                   [&](Entity e) {
                                     rectRender.color.a = 153;
                                     std::cout << "on click\n";
                                   },
                                   [&](Entity e) {
                                     rectRender.color.a = 0;
                                     std::cout << "on release\n";
                                   }));
  }
};
