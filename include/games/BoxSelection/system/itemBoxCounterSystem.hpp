#pragma once

#include "engine/components/Visual.hpp"
#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include <algorithm>

class itemBoxCounterSystem : public System<ItemBoxCounter, Visual> {
  void updateEntity(World &world, Entity e, float dt, ItemBoxCounter &count,
                    Visual &v) override {
    if (!count.start) {
      return;
    }

    if (count.timeElapsed != count.delay) {
      count.timeElapsed = std::clamp(count.timeElapsed + dt, 0.0f, count.delay);
      return;
    } else if (count.items.empty()) {
      count.start = false;

      count.onFinish();

      return;
    }

    Entity current = count.items.front();

    count.items.pop();

    count.count += 1;

    count.timeElapsed = 0.0f;

    /*world.dettachFromAll(current);*/
    /*world.destroy(current);*/
    auto &visual = world.get<Visual>(current);
    visual.color = count.countColor;

    count.onCount();
  }
};
