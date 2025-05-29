#pragma once

#include "engine/core/Types.hpp"
#include "engine/core/World.hpp"
#include "engine/render/IRenderSystem.hpp"
#include "engine/render/RenderJob.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include <tuple>

template <typename... Cs> class RenderSystem : public IRenderSystem
{
public:
  void registerJobs(RenderJobRegistry &jobRegistry, World &world) override
  {
    auto view = world.view<Cs...>();
    for (auto &&tuple : view)
    {
      std::apply(
          [&](Entity entity, Cs &...components)
          {
            auto priority = getPriority(entity, components...);
            RenderJob job = {priority,
                             [&]() { drawFn(world, entity, components...); }};
            jobRegistry.registerJob(std::move(job));
          },
          tuple);
    }
  }

protected:
  virtual uint32_t getPriority(Entity, Cs &...) { return 0; };
  virtual void drawFn(World &, Entity, Cs &...) = 0;
};
