#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Visual.hpp"
#include "engine/render/RenderSystem.hpp"

class RenderRectSystem
    : public RenderSystem<RenderRectangle, Visual, GlobalTransformable> {
  void drawFn(World &w, Entity e, RenderRectangle &r, Visual &v,
              GlobalTransformable &gt) override;

  uint32_t getPriority(Entity e, RenderRectangle &r, Visual &v,
                       GlobalTransformable &gt) override;
};
