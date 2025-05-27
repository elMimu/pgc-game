#include "engine/render/RenderRectSystem.hpp"
#include "engine/shaders/basic2d.hpp"
#include "engine/utils/Projection.hpp"
#include "raylib.h"
#include "rlgl.h"

RenderSystem<RenderRectangle, GlobalTransformable> &RenderRectSystem()
{
  static RenderSystem<RenderRectangle, GlobalTransformable> instance(
      [](Entity e, const RenderRectangle &r, const GlobalTransformable &gt)
      { return r.layer; },
      [](Entity e, const RenderRectangle &r, const GlobalTransformable &gt)
      {
        Projection::update();
        Matrix proj = Projection::get();

        Basic2DShader::draw(proj, gt.worldMatrix, r);
      });
  return instance;
}
