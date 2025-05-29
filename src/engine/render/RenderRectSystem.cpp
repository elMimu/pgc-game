#include "engine/render/RenderRectSystem.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/shaders/basic2d.hpp"
#include "engine/utils/Projection.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <cstdint>

void RenderRectSystem ::drawFn(World &w, Entity e, RenderRectangle &r,
                               GlobalTransformable &gt)
{
  Projection::update();
  Matrix proj = Projection::get();

  Basic2DShader::draw(proj, gt.worldMatrix, r);
};

uint32_t RenderRectSystem::getPriority(Entity e, RenderRectangle &r,
                                       GlobalTransformable &gt)
{
  return r.layer;
}
