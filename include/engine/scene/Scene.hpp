#pragma once
#include "engine/core/World.hpp"
#include "engine/scene/SceneRequest.hpp"

class Scene
{
public:
  Scene(const World &world) : world(world) {};
  virtual ~Scene() = default;
  virtual void inputHandler();
  virtual void onReload() {};
  virtual void onLoad() {};
  virtual void onUpdate(float dt) {};
  virtual void onFinish() {};
  bool isLoaded = false;
  bool isFinished = false;
  const World &world;
  SceneRequest request;
};
