#pragma once

#include "engine/core/World.hpp"
struct ISystem {
    virtual ~ISystem() = default;
    virtual void update(World& world, float dt) = 0;
};
