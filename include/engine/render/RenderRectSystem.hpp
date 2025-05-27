#pragma once

#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/render/RenderSystem.hpp"

// Declaration
// RenderSystem<RenderRectangle, Transformable>& RenderRectSystem();
RenderSystem<RenderRectangle, GlobalTransformable>& RenderRectSystem();
