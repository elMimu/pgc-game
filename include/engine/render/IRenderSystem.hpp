#pragma once

#include "engine/core/World.hpp"
#include "engine/render/RenderJobRegistry.hpp"

class IRenderSystem
{
public:
  virtual ~IRenderSystem() = default;
  virtual void registerJobs(RenderJobRegistry &jobRegistry,
                                     World &world) = 0;
};
