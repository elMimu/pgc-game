#include "list"
#include "raylib.h"
#include "raymath.h"
#include <cstdint>
#include <iostream>
#include <ostream>
#include <set>
#include <stack>
#include <unordered_map>

// DEFINING VIRTUAL RESOLUTION --------- //
#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// ENTITY  ---------- //
using Entity = uint32_t;
const Entity ENTITY_MAX = 100;

// ENTITY MANAGER ---------- //
class EntityManager
{
public:
  Entity nextId = 0;
  std::set<Entity> all;

  Entity create()
  {
    Entity id = nextId++;
    all.insert(id);
    return id;
  }
  void destroy(Entity toDelete) { all.erase(toDelete); }

  void print()
  {
    for (auto &e : all)
    {
      std::cout << e << std::endl;
    }
  }
};

// TRANSFORM COMPONENT --------- //
struct TransformComponent
{
  Vector2 origin;
  Vector2 position;
  Vector2 size;
  float rotation;
};

// RENDER COMPONENT ---------- //
struct RenderComponent
{
  bool active;
  Vector4 color;
};

// COMPONENT MANAGER ---------- //
template <typename T> class ComponentManager
{
public:
  std::unordered_map<Entity, T> all;

  void add(Entity e, const T &component) { all.insert({e, component}); }
  bool has(Entity e) { all.find(e) != all.end(); }
  void remove(Entity e)
  {
    if (!all.find(e))
    {
      return;
    }
    all.erase(e);
  }

  T &get(Entity e) { return all.at(e); }
  std::unordered_map<Entity, T> &getAll() { return all; }

  void print()
  {
    for (auto &[e, _] : getAll())
    {
      std::cout << e << std::endl;
    }
  }
};

// RENDER SYSTEM ---------- //
class RenderSystem
{
public:
  RenderSystem(ComponentManager<TransformComponent> &transformManager,
               ComponentManager<RenderComponent> &renderManager)
      :

        transformManager(transformManager), renderManager(renderManager)
  {
  }

  ComponentManager<TransformComponent> &transformManager;
  ComponentManager<RenderComponent> &renderManager;

  void draw()
  {
    for (auto &[e, d] : renderManager.getAll())
    {
      if (d.active)
      {
        auto &t = transformManager.get(e);
        std::cout << t.position.x << std::endl;
        DrawRectanglePro(
            Rectangle{t.position.x, t.position.y, t.size.x, t.size.y},
            Vector2{t.size.x * t.origin.x, t.size.y * t.origin.y}, t.rotation,
            ColorFromNormalized(d.color));
      }
    }
  }
};

// SCENE INTERFACE --------- //
class IScene
{
public:
  bool isLoaded = false;
  bool isFinished = false;

  void inputHandler()
  {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      isFinished = true;
    }
  }
  virtual void onLoad() = 0;
  void onUpdate(float dt) { inputHandler(); };
  virtual void onFinish() = 0;
};

// SCENE MANAGER ------- //
class SceneManager
{
public:
  std::stack<IScene *> sceneStack;

  void loadCurrent() { sceneStack.top()->onLoad(); }

  void updateCurrent(float dt)
  {
    if (sceneStack.empty())
    {
      return;
    }

    if (sceneStack.top()->isFinished)
    {
      sceneStack.top()->onFinish();
      sceneStack.pop();
      return;
    }

    if (!sceneStack.top()->isLoaded)
    {
      sceneStack.top()->onLoad();
      sceneStack.top()->isLoaded = true;
      return;
    }

    sceneStack.top()->onUpdate(dt);
  }
};

// INTRO SCENE
class IntroScene : public IScene
{
public:
  void onLoad() { std::cout << "Intro Scene Loaded" << std::endl; };
  void onUpdate(float dt) {};
  void onFinish() { std::cout << "Intro Scene Finished" << std::endl; };
};

// SCENE_2
class GameplayScene : public IScene
{
public:
  void onLoad() { std::cout << "Gameplay Scene Loaded" << std::endl; };
  void onUpdate(float dt) {};
  void onFinish() { std::cout << "Gameplay Scene Finished" << std::endl; };
};
// SCENE_3
class EndScene : public IScene
{
public:
  void onLoad() { std::cout << "End Scene Loaded" << std::endl; };
  void onUpdate(float dt) {};
  void onFinish() { std::cout << "End Scene Finished" << std::endl; };
};

// GAME ---------- //
class Game
{
public:
  // Manager
  EntityManager entityManager;
  ComponentManager<TransformComponent> transformManager;
  ComponentManager<RenderComponent> renderManager;

  // System
  RenderSystem renderSystem = RenderSystem(transformManager, renderManager);

  // Scene Manager
  SceneManager sceneManager;

  // Scenes
  IntroScene introScene;
  GameplayScene gameplayScene;
  EndScene endSCene;

  void load()
  {
    sceneManager.sceneStack.push(&endSCene);
    sceneManager.sceneStack.push(&gameplayScene);
    sceneManager.sceneStack.push(&introScene);
  }

  // Entities
  // Entity a = entityManager.create();
  // Entity b = entityManager.create();
  //
  // // REGISTER
  // void attachManagers()
  // {
  //   transformManager.add(
  //       a, TransformComponent{Vector2{0.0f, 0.0f},
  //                             Vector2{VIRTUAL_X / 2.0, VIRTUAL_Y / 2.0},
  //                             Vector2{10.0f, 10.0f}, 0.0f});
  //   transformManager.add(b, TransformComponent{Vector2{0.5f, 0.5f},
  //                                              Vector2{0.0, 0.0f},
  //                                              Vector2{10.0f, 10.0f},
  //                                              0.0f});
  //
  //   renderManager.add(a, {true, {1.0f, 0.0f, 0.0f, 1.0f}});
  //   renderManager.add(b, {true, {0.0f, 1.0f, 0.0f, 1.0f}});
  // }

  // GAMELOOP UPDATA
  void update(float dt)
  {
    sceneManager.updateCurrent(dt);
    // renderSystem.renderManager.print();
    // renderSystem.draw();
  };
};

// GAME STARTING POINT ---------- //
int main(void)
{

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(VIRTUAL_X, VIRTUAL_Y, "First Minigame");

  SetTargetFPS(60);

  Game game = Game();
  game.load();

  std::cout << "log:" << std::endl;

  while (!WindowShouldClose())
  {
    float time = GetTime();
    float dt = GetFrameTime();

    // window
    BeginDrawing();
    ClearBackground(DARKGRAY);

    // game
    game.update(dt);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
