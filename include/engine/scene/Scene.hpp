#pragma once

#include "engine/scene/SceneRequest.hpp"

class Scene
{
public:
  virtual void inputHandler();
  virtual void onLoad() = 0;
  virtual void onUpdate(float dt);
  virtual void onFinish() = 0;
  bool isLoaded = false;
  bool isFinished = false;
  SceneRequest request;
};
