#include "engine/render/RenderTextSystem.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "raylib.h"

void RenderTextSystem::drawFn(World &w, Entity e, RenderText &rt,
                              Transformable &t, GlobalTransformable &gt)
{
  constexpr float testFont = 100.0f;
  Vector2 measuredSize =
      MeasureTextEx(rt.font, rt.text.c_str(), testFont, rt.spacing);

  float normalizedWidth = measuredSize.x / testFont;
  float normalizedHeight = measuredSize.y / testFont;

  Vector2 scale = TransformUtils::getScaleFromMatrix(gt.worldMatrix);
  float fontSize = scale.x / normalizedWidth * 0.82;

  Vector2 finalSize = {normalizedWidth * fontSize, normalizedHeight * fontSize};

  Vector2 origin = {finalSize.x * t.origin.x, finalSize.y * t.origin.y};

  Vector2 worldPos = Vector2Transform(t.origin, gt.worldMatrix);

  float rotation = TransformUtils::getDegRotationFromMatrix(gt.worldMatrix);

  DrawTextPro(rt.font, rt.text.c_str(), worldPos, origin, rotation, fontSize,
              rt.spacing, rt.color);
}

uint32_t RenderTextSystem::getPriority(Entity e, RenderText &rt,
                                       Transformable &t,
                                       GlobalTransformable &gt)
{
  return rt.priority;
};
