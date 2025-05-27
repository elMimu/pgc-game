#pragma once

#include "engine/render/IRenderSystem.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include "engine/render/RenderSystem.hpp"
#include <vector>

class RenderSystemRegistry
{
public:
  template <typename C, typename... Cs>
  void registerSystem(RenderSystem<C, Cs...> &system)
  {
    allRenderSystems.push_back(&system);
  }

  void registerAllComponentsJobs(RenderJobRegistry &jobRegistry, World &world)
  {

    for (auto &render : allRenderSystems)
    {
      render->registerJobs(jobRegistry, world);
    }
  };

private:
  std::vector<IRenderSystem *> allRenderSystems;
};
