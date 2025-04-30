#pragma once

#include "engine/scene/IScene.hpp"
#include "engine/scene/SceneRequest.hpp"
#include "raylib.h"

class Scene : public IScene
{
public:
  SceneRequest request;
  bool isLoaded = false;
  bool isFinished = false;

  void inputHandler()
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      isFinished = true;
    }
  }

  void onUpdate(float dt) { inputHandler(); };
};
