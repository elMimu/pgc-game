#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/render/RenderSystem.hpp"
#include "raylib.h"
#include <cstdint>

class RenderTextSystem
    : public RenderSystem<RenderText, Transformable, GlobalTransformable>
{
  uint32_t getPriority(Entity e, RenderText &rt, Transformable &t,
                       GlobalTransformable &gt) override;

  void drawFn(World &, Entity, RenderText &rt, Transformable &t,
              GlobalTransformable &gt) override;
};
