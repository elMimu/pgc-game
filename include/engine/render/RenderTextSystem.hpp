#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/render/RenderSystem.hpp"
#include "engine/systems/GlobalTransformSystem.hpp"
#include "raylib.h"
#include <cstdint>

class RenderTextSystem : public RenderSystem<RenderText, GlobalTransformable>
{
  uint32_t getPriority(Entity e, RenderText &rt,
                       GlobalTransformable &gt) override;


  void drawFn(World &, Entity, RenderText &rt,
              GlobalTransformable &gt) override;
};
