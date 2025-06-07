#pragma once
#include "engine/core/World.hpp"
#include "engine/scene/SceneRequest.hpp"

class Scene {
public:
  Scene(World &world) : world(world) {};
  virtual ~Scene() = default;

  virtual void inputHandler() = 0;
  virtual void onReload() {};
  virtual void onLoad() {};
  virtual void onUpdate(float dt) {};
  virtual void onFinish() {};

  template <typename T> void addRequest(SceneRequest::Action action) {
    static_assert(std::is_base_of_v<Scene, T>, "T must derive from Scene");
    request.action = action;
    request.factory = [](World &world) -> std::unique_ptr<Scene> {
      return std::make_unique<T>(world);
    };
  };

  void addRequest(SceneRequest::Action action) {
    request.action = action;
    request.factory = [](World &world) -> std::unique_ptr<Scene> {
      return nullptr;
    };
  };

  void clearRequest() {
    request.action = SceneRequest::Action::NONE;
    request.factory = nullptr;
  }

  bool isLoaded = false;
  bool isFinished = false;
  bool onFinishCalled = false;
  World &world;
  SceneRequest request;
};
