#include "engine/scene/SceneManager.hpp"
#include "engine/scene/SceneRequest.hpp"

bool SceneManager::currentSceneHasQuery() {
  return sceneStack.back()->request.action != SceneRequest::Action::NONE;
}

bool SceneManager::currentSceneIsLoaded() {
  return sceneStack.back()->isLoaded;
}

void SceneManager::handleSceneRequest(World &world) {
  SceneRequest &currentSceneRequest = sceneStack.back()->request;

  switch (currentSceneRequest.action) {
  case SceneRequest::Action::PUSH:
    if (currentSceneRequest.factory) {
      sceneStack.push_back(currentSceneRequest.factory(world));
      auto &previewsScene = sceneStack[sceneStack.size() - 2];
      previewsScene->clearRequest();
    }
    break;

  case SceneRequest::Action::POP:
    if (!sceneStack.empty()) {
      sceneStack.back()->isFinished = true;
      sceneStack.back()->onFinish();
      sceneStack.back()->clearRequest();
      sceneStack.pop_back();
    }
    break;

  case SceneRequest::Action::RELOAD:
    if (!sceneStack.empty()) {
      sceneStack.back()->isFinished = true;
      sceneStack.back()->onFinish();
      sceneStack.back()->clearRequest();
      sceneStack.pop_back();
      sceneStack.back()->clearRequest();
      sceneStack.back()->onReload();
    }
    break;

  case SceneRequest::Action::REPLACE:
    if (!sceneStack.empty()) {
      sceneStack.back()->isFinished = true;
      sceneStack.back()->onFinish();
      sceneStack.back()->clearRequest();
      sceneStack.pop_back();
      if (currentSceneRequest.factory) {
        sceneStack.push_back(currentSceneRequest.factory(world));
      }
    }
    break;

  case SceneRequest::Action::CLEAR:
    sceneStack.back()->isFinished = true;
    sceneStack.back()->onFinish();
    sceneStack.clear();
    if (currentSceneRequest.factory) {
      sceneStack.push_back(currentSceneRequest.factory(world));
    }
    break;

  case SceneRequest::Action::NONE:
    return;

  default:
    break;
  }

  // Clear request after handling
  currentSceneRequest.action = SceneRequest::Action::NONE;
  currentSceneRequest.factory = nullptr;
}

void SceneManager::update(World &world, float dt) {
  if (sceneStack.empty()) {
    return;
  }

  if (sceneStack.back()->isFinished) {
    if (sceneStack.back()->onFinishCalled) {
      return;
    }

    sceneStack.back()->onFinish();
    sceneStack.back()->onFinishCalled = true;

    if (currentSceneHasQuery()) {
      handleSceneRequest(world);
      return;
    }
  }

  if (!currentSceneIsLoaded()) {
    sceneStack.back()->onLoad();
    sceneStack.back()->isLoaded = true;
    return;
  }

  if (currentSceneHasQuery()) {
    handleSceneRequest(world);
    return;
  }

  sceneStack.back()->inputHandler();
  sceneStack.back()->onUpdate(dt);
}
