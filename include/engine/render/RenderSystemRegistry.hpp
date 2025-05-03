#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/render/RenderSystem.hpp"
#include <memory>
#include <vector>

class RenderSystemRegistry
{
public:
  template <typename T, typename... Args>
  void registerRenderSystem(Args &&...args)
  {
    static_assert(std::is_base_of<RenderSystem, T>::value);
    allRenderSystems.push_back(
        std::make_unique<T>(std::forward<Args>(args)...));
  }

  void registerAllComponentsJobs(ComponentRegistry &component);

private:
  std::vector<std::unique_ptr<RenderSystem>> allRenderSystems;
};
