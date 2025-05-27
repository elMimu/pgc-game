#pragma once

#include "engine/core/World.hpp"
#include "engine/render/IRenderSystem.hpp"
#include "engine/render/RenderJob.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include <cstdint>
#include <functional>
#include <tuple>

template <typename C, typename... Cs> class RenderSystem : public IRenderSystem
{
public:
  using DrawFn = std::function<void(Entity, const C &, const Cs &...)>;
  using PriorityFn =
      std::function<std::uint32_t(Entity, const C &, const Cs &...)>;

  RenderSystem(PriorityFn priorityFn, DrawFn drawFn)
      : getPriority(priorityFn), drawFn(drawFn)
  {
  }

  void registerJobs(RenderJobRegistry &jobRegistry, World &world) override
  {
    auto view = world.view<C, Cs...>();

    for (auto &&entry : view)
    {
      std::apply(
          [&](Entity entity, const C &c, const Cs &...rest)
          {
            auto priority = getPriority(entity, c, rest...);
            RenderJob job = {priority, [=]() { drawFn(entity, c, rest...); }};
            jobRegistry.registerJob(std::move(job));
          },
          entry);
    }
  }

private:
  PriorityFn getPriority;
  DrawFn drawFn;
};
