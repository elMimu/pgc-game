#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "raylib.h"
#include "raymath.h"
#include <algorithm>

class FloatOutSystem
    : public System<FloatOut, Transformable, GlobalTransformable, Visual> {
  void updateEntity(World &world, Entity e, float dt, FloatOut &fo,
                    Transformable &t, GlobalTransformable &gt,
                    Visual &v) override {
    if (!fo.loaded) {
      load(fo, v, t, gt);
      fo.loaded = true;
    }

    if (!fo.play) {
      return;
    }

    if (isFinished(fo.progress) && fo.play) {
      fo.play = false;
      world.dettachFromAll(e);
      world.destroy(e);
      return;
    }

    v.color.a = 255 * fo.progress;
    t.position = Vector2Lerp(fo.startPos, fo.endPos, fo.progress);
    t.size = Vector2Lerp(fo.startScale, fo.endScale, fo.easing(fo.progress));
    gt.dirty = true;

    fo.progress = std::clamp(fo.progress + fo.speed * dt, 0.0f, 1.0f);
  }

  void load(FloatOut &fo, Visual &v, Transformable &t,
            GlobalTransformable &gt) {
    v.color.a = 0.0f;
    t.position = {fo.startPos.x, fo.startPos.y};
    t.size = {fo.startScale.x, fo.startScale.y};
    gt.dirty = true;
  }

  inline bool isFinished(float progress) { return progress == 1.0f; }
};
