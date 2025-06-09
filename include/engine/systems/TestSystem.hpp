#pragma once

#include "engine/components/Transformable.hpp"
#include "engine/systems/System.hpp"

class TestSystem : public System<Transformable>
{
  void updateEntity(World &world, Entity e, float dt, Transformable &t) override
  {
    t.rotation += dt * RAD2DEG;
  };
};
