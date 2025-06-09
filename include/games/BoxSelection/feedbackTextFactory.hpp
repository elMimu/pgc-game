#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "engine/core/World.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"

class FeedbackTextFactory {
public:
  static Entity create(World &world, const Transformable &t, const Visual &v,
                       const RenderText &rt, const FloatOut &ft) {

    Entity text = world.entityManager.create();
    world.attach<Transformable>(text, t);
    world.attach<GlobalTransformable>(text, {});
    world.attach<Visual>(text, v);
    world.attach<RenderText>(text, rt);
    world.attach<FloatOut>(text, ft);

    return text;
  };
};
