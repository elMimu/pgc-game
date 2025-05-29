#include "engine/render/RenderTextSystem.hpp"
#include "engine/utils/PrintMatrix.hpp"

void RenderTextSystem::drawFn(World &w, Entity e, RenderText &rt,
                              GlobalTransformable &gt)
{
  static bool once = false;
  ;
  Vector2 position = {gt.worldMatrix.m12, gt.worldMatrix.m13};
  float scale = gt.worldMatrix.m10;

  if (!once)
  {
    std::cout << scale << "\n";
    std::cout << position.x << " " << position.y << "\n";
    PrintMatrix(gt.worldMatrix);
    once = true;
  }

  DrawTextEx(GetFontDefault(), rt.text.c_str(), position, rt.fontSize * scale,
             rt.spacing, rt.color);
};

uint32_t RenderTextSystem::getPriority(Entity e, RenderText &rt,
                                       GlobalTransformable &gt)
{
  return rt.priority;
};
