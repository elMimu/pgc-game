#pragma once

#include "engine/core/World.hpp"
#include <functional>
#include <memory>
class Scene;

struct SceneRequest {
  enum class Action {
    CLEAR,
    PUSH,
    POP,
    RELOAD,
    REPLACE,
    NONE,
  };
  Action action = Action::NONE;
  std::function<std::unique_ptr<Scene>(World &)> factory = nullptr;
};
