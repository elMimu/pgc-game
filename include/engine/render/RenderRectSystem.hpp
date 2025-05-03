#include "engine/components/ComponentManager.hpp"
#include "engine/components/ComponentRegistry.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/render/RenderJob.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include "raylib.h"

#include <cstdint>

class RenderRectSystem
{
public:
  struct RenderRectComponent
  {
    uint32_t layer;
    Vector4 color;
  };

  RenderJob createSystemJob(Entity e, ComponentRegistry &components,
                            RenderJobRegistry &jobRegistry)
  {
    // check if RenderRectComponentManagerExists
    // if don't,  create;
    ComponentManager<RenderRectComponent> renderRectManager =
        components.getOrRegisterManager<RenderRectComponent>();

    ComponentManager<TransformComponent> transformManager =
        components.getOrRegisterManager<TransformComponent>();

    RenderRectComponent render = renderRectManager.getEntityComponent(e);
    TransformComponent t = transformManager.getEntityComponent(e);

    return {render.layer, [&render, &t]()
            {
              DrawRectanglePro(
                  Rectangle{t.position.x, t.position.y, t.size.x, t.size.y},
                  Vector2{t.size.x * t.origin.x, t.size.y * t.origin.y},
                  RAD2DEG * t.rotation, ColorFromNormalized(render.color));
            }};
  }

  void registerSystemAllJobs(ComponentRegistry &components,
                             RenderJobRegistry &jobRegistry)
  {
    ComponentManager<RenderRectComponent> renderRectManager =
        components.getOrRegisterManager<RenderRectComponent>();
    for (auto &[e, _] : renderRectManager.getManagerMap())
    {
      jobRegistry.registerJob(createSystemJob(e, components, jobRegistry));
    }
  };
};
