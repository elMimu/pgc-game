#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/systems/System.hpp"
#include "engine/utils/TransformUtils.hpp"

class GlobalTransformSystem : public System<GlobalTransformable, Transformable>
{
  void updateEntity(World &world, Entity e, float dt,
                    GlobalTransformable &globalT, Transformable &t) override
  {
    globalT.worldMatrix = TransformUtils::getWorldMatrix(world, e, t);
  };
};
