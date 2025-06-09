#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/render/RenderSystem.hpp"
#include <cstdint>

class RenderTextSystem : public RenderSystem<RenderText, Visual, Transformable,
                                             GlobalTransformable> {
  uint32_t getPriority(Entity e, RenderText &rt, Visual &v, Transformable &t,
                       GlobalTransformable &gt) override;

  void drawFn(World &, Entity, RenderText &rt, Visual &v, Transformable &t,
              GlobalTransformable &gt) override;
};
