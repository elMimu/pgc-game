#pragma once

#include "engine/components/Clickable.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "games/BoxSelection/itemBoxFactory.hpp"
#include "raylib.h"
#include <cstdint>
#include <functional>

class ClickableBoxFactory {
public:
  static Entity creatClickableBox(World &world, int quantity, Vector2 origin,
                                  Vector2 position, Vector2 size,
                                  float rotation, uint32_t priority,
                                  Color boxColor, Color itemColor,
                                  std::function<void(Entity)> onRelease) {
    Entity box =
        itemBoxFactory::createItemBox(world, quantity, origin, position, size,
                                      rotation, priority, boxColor, itemColor);

    Entity cover = createCover(world, box, priority);
    setupSystem(world, cover, onRelease);
    return box;
  }

private:
  static Entity createCover(World &world, Entity parent, uint32_t priority) {
    Entity cover = world.entityManager.create();
    world.attach<Transformable>(
        cover,
        Transformable({0.5f, 0.5f}, {0.5f, 0.5f}, {1.0f, 1.0f}, 0.0f, parent));
    world.attach<GlobalTransformable>(cover, {});
    world.attach<Visual>(cover,
                         {Vector4{0.0f, 0.0f, 0.0f, 0.0f}, priority + 1});
    world.attach<RenderRectangle>(cover, {});
    return cover;
  }

  static void setupSystem(World &world, Entity e,
                          std::function<void(Entity)> onRelease) {
    auto &visual = world.get<Visual>(e);
    world.attach<Clickable>(
        e, Clickable([&visual](Entity e) { visual.color.a = 153; },
                     [&visual, onRelease](Entity e) {
                       onRelease(e);
                       visual.color.a = 0;
                     }));
  }
};
