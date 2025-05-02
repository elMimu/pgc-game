#include "engine/scene/Scene.hpp"
#include "raylib.h"

void Scene::inputHandler()
{
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    isFinished = true;
  }
}

void Scene::onUpdate(float dt)
{
  inputHandler();
};
