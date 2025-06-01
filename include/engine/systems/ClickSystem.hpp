#pragma once

#include "engine/components/Clickable.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/state/InputState.hpp"
#include "engine/systems/System.hpp"
#include "raylib.h"

class ClickSystem : public System<Clickable, GlobalTransformable> {
  void updateEntity(World &world, Entity e, float dt, Clickable &c,
                    GlobalTransformable &gt) override {
    if (!c.active)
      return;

    auto &input = world.getUserState<InputState>();

    if (input.pointerDown &&
        isPointInsideEntity(input.pointerPos, gt.worldMatrix)) {
      if (c.onClick) {
        c.onClick(e);
      }
    }

    if (input.pointerReleased &&
        isPointInsideEntity(input.pointerPos, gt.worldMatrix)) {
      if (c.onRelease) {
        c.onRelease(e);
      }
    }
  }

  Vector2 transformPointToLocal(Vector2 &screenPoint, Matrix &worldMatrix) {
    Matrix inverse = MatrixInvert(worldMatrix);

    Vector3 worldVec3 = {screenPoint.x, screenPoint.y, 0.0f};
    Vector3 localVec3 = Vector3Transform(worldVec3, inverse);

    return {localVec3.x, localVec3.y};
  }

  bool isPointInsideEntity(Vector2 &screenPoint, Matrix &worldMatrix) {
    Vector2 localPoint = transformPointToLocal(screenPoint, worldMatrix);

    return localPoint.x >= 0.0f && localPoint.x <= 1.0f &&
           localPoint.y >= 0.0f && localPoint.y <= 1.0f;
  }
};
