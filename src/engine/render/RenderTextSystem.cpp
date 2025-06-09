#include "engine/render/RenderTextSystem.hpp"
#include "engine/components/Visual.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "raylib.h"

void RenderTextSystem::drawFn(World &w, Entity e, RenderText &rt, Visual &v,
                              Transformable &t, GlobalTransformable &gt) {
  float baseWidth = rt.baseWidth;
  if (rt.dirty) {
    baseWidth = FontLoader::getBaseTextWidth(rt.text, rt.font);
  }

  Vector2 scale = TransformUtils::getScaleFromMatrix(gt.worldMatrix);

  float fontSize = (scale.x / baseWidth) * rt.font.baseSize;

  Vector2 finalSize = {
      baseWidth * fontSize / rt.font.baseSize,
      rt.font.baseSize * fontSize / rt.font.baseSize // = fontSize
  };

  Vector2 origin = {finalSize.x * t.origin.x, finalSize.y * t.origin.y};

  Vector2 worldPos = Vector2Transform(t.origin, gt.worldMatrix);

  float rotation = TransformUtils::getDegRotationFromMatrix(gt.worldMatrix);

  DrawTextPro(rt.font, rt.text.c_str(), worldPos, origin, rotation, fontSize,
              0.0f, v.color);
}

uint32_t RenderTextSystem::getPriority(Entity e, RenderText &rt, Visual &v,

                                       Transformable &t,
                                       GlobalTransformable &gt) {
  return v.layer;
};
