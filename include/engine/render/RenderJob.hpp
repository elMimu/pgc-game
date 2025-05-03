#pragma once

#include <cstdint>
#include <functional>

struct RenderJob
{
  std::uint32_t layer;
  std::function<void()> drawFn;
};
