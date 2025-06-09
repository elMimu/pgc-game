#pragma once

#include "engine/render/IRenderSystem.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include "engine/render/RenderSystem.hpp"
#include "engine/systems/ISystem.hpp"
#include <memory>
#include <vector>

class RenderSystemRegistry
{
public:
  template <typename T> void registerRender()
  {
    allRenderSystems.push_back(std::move(createRender<T>()));
  }

  void registerAllComponentsJobs(RenderJobRegistry &jobRegistry, World &world)
  {

    for (auto &render : allRenderSystems)
    {
      render->registerJobs(jobRegistry, world);
    }
  };

private:
  std::vector<std::unique_ptr<IRenderSystem>> allRenderSystems;

  template <typename T> std::unique_ptr<T> createRender()
  {
    static_assert(std::is_base_of<IRenderSystem, T>::value,
                  "T must be derived from ISystem");
    return std::make_unique<T>();
  };
};
