#pragma once

#include "engine/core/Types.hpp"
#include <functional>

struct Clickable
{
  bool active = true;
  std::function<void(Entity)> onClick = nullptr;
  std::function<void(Entity)> onRelease = nullptr;

  Clickable(std::function<void(Entity)> onClick,
            std::function<void(Entity)> onRelease)
      : onClick(onClick), onRelease(onRelease)
  {
  }
};
