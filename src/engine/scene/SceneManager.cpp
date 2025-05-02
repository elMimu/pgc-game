#include "Scene.cpp"
#include "engine/scene/IScene.hpp"
#include "engine/scene/SceneRequest.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

class SceneManager
{
public:
  // ALL SCENENES MAP;
  std::unordered_map<std::string, Scene *> sceneMap;

  // SCENE STACK;
  std::vector<Scene *> sceneStack;

  bool currentSceneHasQuery()
  {
    return sceneStack.back()->request.type != SceneRequest::RequestType::NONE;
  }

  bool currentSceneIsLoaded() { return sceneStack.back()->isLoaded; }

  // HANDLE SCENE QUERY
  void handleSceneQuery()
  {
    SceneRequest currentSceneRequest = sceneStack.back()->request;

    switch (currentSceneRequest.type)
    {
    case SceneRequest::RequestType::REPLACE:
      sceneStack.pop_back();
      pushScene(currentSceneRequest.sceneName);
      break;
    case SceneRequest::RequestType::STACK:
      pushScene(currentSceneRequest.sceneName);
      break;
      // case SceneRequest::RequestType::POP:
    default:
      sceneStack.pop_back();
      break;
    };
  }

  void update(float dt)
  {
    updateScene(dt);
    draw();
  }

  void draw() {}

  // UPDATE
  void updateScene(float dt)
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

  // REPLACE SCENE:
  void replace(std::string sceneName)
  {
    sceneMap.clear();
    pushScene(sceneName);
  }

  // CHECK IF SCENE EXISTS:
  bool hasScene(std::string sceneName)
  {
    return sceneMap.find(sceneName) != sceneMap.end();
  }

  // PUSH SCENE TO STACK
  void pushScene(std::string sceneName)
  {
    IScene *toStack;
    toStack = getScene(sceneName);
    if (toStack == nullptr)
    {
      return;
    }
  }

  // RETRIEVE SCENE FROM MAP
  IScene *getScene(std::string sceneName)
  {
    if (!hasScene(sceneName))
    {
      std::cout << "Scene Doesnt exist" << std::endl;
      return nullptr;
    }

    return sceneMap.at(sceneName);
  }

  // ADD SCENE TO GENERAL
  void addScene(const std::string sceneName, Scene &scene)
  {
    sceneMap.insert({sceneName, &scene});
  }

  // ERASE SCENE FROM GENERAL
  void eraseScene(const std::string sceneName) { sceneMap.erase(sceneName); }
};
