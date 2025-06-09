#pragma once

#include "engine/systems/ISystem.hpp"

template <typename... Cs> class System : public ISystem
{
public:
  virtual ~System() = default;
  void update(World &world, float dt) override
  {
    auto view = world.view<Cs...>();
    for (auto &&tuple : view)
    {
      std::apply([&](Entity e, Cs &...components)
                 { updateEntity(world, e, dt, components...); }, tuple);
    }
  };

protected:
  virtual void updateEntity(World &world, Entity e, float dt, Cs &...) = 0;
};
