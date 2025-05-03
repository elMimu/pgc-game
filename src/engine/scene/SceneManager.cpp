#include "engine/scene/SceneManager.hpp"
#include "engine/scene/Scene.hpp"
#include "engine/scene/SceneRequest.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

bool SceneManager::currentSceneHasQuery()
{
  return sceneStack.back()->request.type != SceneRequest::RequestType::NONE;
}

bool SceneManager::currentSceneIsLoaded()
{
  return sceneStack.back()->isLoaded;
}

void SceneManager::handleSceneQuery()
{
  SceneRequest currentSceneRequest = sceneStack.back()->request;

  switch (currentSceneRequest.type)
  {
  case SceneRequest::RequestType::REPLACE:
    sceneStack.pop_back();
    stackScene(currentSceneRequest.sceneName);
    break;
  case SceneRequest::RequestType::STACK:
    stackScene(currentSceneRequest.sceneName);
    break;
    // case SceneRequest::RequestType::POP:
  default:
    sceneStack.pop_back();
    break;
  };
}

void SceneManager::update(float dt)
{
  if (sceneStack.empty())
  {
    return;
  }

  if (currentSceneHasQuery())
  {
    handleSceneQuery();
    return;
  }

  if (!currentSceneIsLoaded())
  {
    sceneStack.back()->onLoad();
    sceneStack.back()->isLoaded = true;
    return;
  }

  sceneStack.back()->onUpdate(dt);
}

void SceneManager::replace(std::string sceneName)
{
  sceneMap.clear();
  stackScene(sceneName);
}

bool SceneManager::hasScene(std::string sceneName)
{
  return sceneMap.find(sceneName) != sceneMap.end();
}

void SceneManager::stackScene(std::string sceneName)
{
  Scene *toStack;
  toStack = getScene(sceneName);
  if (toStack == nullptr)
  {
    return;
  }
}

Scene *SceneManager::getScene(std::string sceneName)
{
  if (!hasScene(sceneName))
  {
    std::cout << "Scene Doesnt exist" << std::endl;
    return nullptr;
  }

  return sceneMap.at(sceneName);
}

void SceneManager::addScene(const std::string sceneName, Scene &scene)
{
  sceneMap.insert({sceneName, &scene});
}

void SceneManager::eraseScene(const std::string sceneName)
{
  sceneMap.erase(sceneName);
}
