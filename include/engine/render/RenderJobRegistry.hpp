#pragma once

#include "RenderJob.hpp"
#include <vector>

class RenderJobRegistry
{
public:
  std::vector<RenderJob> allRenderJobs;
  void registerJob(RenderJob r);
  void flush();
};
