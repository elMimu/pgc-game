#pragma once

#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include <algorithm>

class itemBoxCounterSystem : public System<ItemBoxCounter> {
  void updateEntity(World &world, Entity e, float dt,
                    ItemBoxCounter &count) override {
    if (!count.start) {
      return;
    }

    if (count.timeElapsed != count.delay) {
      count.timeElapsed = std::clamp(count.timeElapsed + dt, 0.0f, count.delay);
      return;
    }

    Entity current = count.items.front();

    count.items.pop();

    count.count += 1;

    std::cout << count.count << "\n";

    count.timeElapsed = 0.0f;

    world.dettachFromAll(current);
    world.destroy(current);

    if (count.items.empty()) {
      count.start = false;

      world.dettachFromAll(current);
      world.destroy(current);

      return;
    }
  }
};
