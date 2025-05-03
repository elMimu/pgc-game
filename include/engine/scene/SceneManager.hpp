#include "engine/scene/Scene.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class SceneManager
{
private:
  std::unordered_map<std::string, Scene *> sceneMap;
  std::vector<Scene *> sceneStack;

  void update(float dt);
  bool currentSceneHasQuery();
  bool currentSceneIsLoaded();
  void handleSceneQuery();
  bool hasScene(std::string sceneName);
  void stackScene(std::string sceneName);
  Scene *getScene(std::string sceneName);
  void addScene(const std::string sceneName, Scene &scene);
  void eraseScene(const std::string sceneName);
  void replace(std::string sceneName);
};
