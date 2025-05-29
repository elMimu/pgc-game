#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/render/RenderSystem.hpp"

class RenderRectSystem
    : public RenderSystem<RenderRectangle, GlobalTransformable>
{
  void drawFn(World &w, Entity e, RenderRectangle &r,
              GlobalTransformable &gt) override;

  uint32_t getPriority(Entity e, RenderRectangle &r,
                       GlobalTransformable &gt) override;
};
