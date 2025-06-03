#include "engine/render/RenderRectSystem.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Visual.hpp"
#include "engine/shaders/basic2d.hpp"
#include "engine/utils/Projection.hpp"
#include "raylib.h"
#include "rlgl.h"
#include <cstdint>

void RenderRectSystem ::drawFn(World &w, Entity e, RenderRectangle &r,
                               Visual &v, GlobalTransformable &gt) {
  Projection::update();
  Matrix proj = Projection::get();

  Basic2DShader::draw(proj, gt.worldMatrix, v);
};

uint32_t RenderRectSystem::getPriority(Entity e, RenderRectangle &r, Visual &v,
                                       GlobalTransformable &gt) {
  return v.layer;
}
