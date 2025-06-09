#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/ScaleLerp.hpp"
#include "raymath.h"
#include <algorithm>

class ScaleLerpSystem
    : public System<ScaleLerp, Transformable, GlobalTransformable> {
  void updateEntity(World &world, Entity e, float dt, ScaleLerp &sl,
                    Transformable &t, GlobalTransformable &gt) override {

    if (Vector2Equals(sl.to, sl.from)) {
      return;
    }

    if (sl.progress == 0.0f) {
      sl.from = t.size;
    }

    if (sl.progress >= 1.0f) {
      sl.from = sl.to;
      t.size = sl.to;
      sl.progress = 0.0f;
      gt.dirty = true;
      sl.callback();
      return;
    }

    sl.progress = std::clamp(sl.progress + sl.speed * dt, 0.0f, 1.0f);
    float easedProgress = sl.easing(sl.progress);
    t.size = Vector2Lerp(sl.from, sl.to, easedProgress);
    gt.dirty = true;
  }
};
