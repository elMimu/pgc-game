#include "engine/render/RenderRegistry.hpp"
#include <algorithm>

void RenderJobRegistry::registerJob(RenderJob r)
{
  auto it = std::upper_bound(allRenderJobs.begin(), allRenderJobs.end(), r,
                             [](const RenderJob &a, const RenderJob &b)
                             { return a.layer < b.layer; });

  allRenderJobs.insert(it, r);
}

void RenderJobRegistry::flush()
{
  for (auto job : allRenderJobs)
  {
    job.drawFn();
  }

  allRenderJobs.clear();
}
