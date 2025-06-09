

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/ScaleAnimation.hpp"
#include "raymath.h"
#include <algorithm>

class ScaleAnimationSystem
    : public System<ScaleAnimation, Transformable, GlobalTransformable> {
  void updateEntity(World &world, Entity e, float dt, ScaleAnimation &sa,
                    Transformable &t, GlobalTransformable &gt) override {
    if (!sa.play) {
      return;
    }

    if (sa.progress == 1.0f) {
      // finish
      sa.callback();
      sa.play = false;
      return;
    }

    t.size = Vector2Lerp(sa.startScale, sa.endScale, sa.easing(sa.progress));

    sa.progress = std::clamp(sa.progress + sa.speed * dt ,0.0f, 1.0f);
  }
};
