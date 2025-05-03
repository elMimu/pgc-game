#include "engine/render/RenderSystemRegistry.hpp"

void RenderSystemRegistry::registerAllComponentsJobs(
    ComponentRegistry &component)
{

  for (auto &render : allRenderSystems)
  {
    render->registerAllSystemJobs(component);
  }
}
