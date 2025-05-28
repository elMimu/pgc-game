#pragma once

#include "engine/core/MapRegistry.hpp"
#include "engine/scene/Scene.hpp"
#include "engine/scene/SceneRequest.hpp"
#include <memory>
#include <utility>
#include <vector>

class SceneManager
{
public:
  void update(World &world, float dt);

  template <typename T> void pushScene(World &world)
  {
    sceneStack.push_back(std::move(createScene<T>(world)));
  };

private:
  std::vector<std::unique_ptr<Scene>> sceneStack;

  bool currentSceneHasQuery();
  bool currentSceneIsLoaded();
  void handleSceneRequest(World &world);

  template <typename T> std::unique_ptr<Scene> createScene(World &world)
  {
    static_assert(std::is_base_of<Scene, T>::value,
                  "T must be derived from Scene");
    return std::make_unique<T>(world);
  }
};
