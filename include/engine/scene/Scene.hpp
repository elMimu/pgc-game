#pragma once
#include "engine/core/World.hpp"
#include "engine/scene/SceneRequest.hpp"

class Scene
{
public:
  Scene(World &world) : world(world) {};
  virtual ~Scene() = default;

  virtual void inputHandler() = 0; 
  virtual void onReload() {};
  virtual void onLoad() {};
  virtual void onUpdate(float dt) {};
  virtual void onFinish() {};

  bool isLoaded = false;
  bool isFinished = false;
  World &world;
  SceneRequest request;
};

