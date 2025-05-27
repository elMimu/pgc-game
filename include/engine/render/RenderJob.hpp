#pragma once

#include <cstdint>
#include <functional>

struct RenderJob
{
  std::uint32_t priority;
  std::function<void()> draw;
};
