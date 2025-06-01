#pragma once

#include "engine/components/Clickable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/state/InputState.hpp"
#include "engine/systems/System.hpp"

class ClickSystem : public System<Clickable, Transformable>
{
  void updateEntity(World &world, Entity e, float dt, Clickable &c,
                    Transformable &t) override
  {
    if (!c.active)
      return;

    // auto *input = world.getUserState<InputState>();
    // if (input->pointerReleased && input->pointInside(input->pointerPos, t))
    // {
    //   if (c.onClick)
    //     c.onClick(e);
    // }
  }
};
