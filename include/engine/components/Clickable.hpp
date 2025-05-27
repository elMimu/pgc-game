#include "engine/core/Types.hpp"
#include <functional>

struct Clickable
{
  bool active = true;
  std::function<void(Entity)> onClick = nullptr;
};
