#include "list"
#include "raylib.h"
#include "raymath.h"
#include <cstdint>
#include <iostream>
#include <ostream>
#include <set>
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
    renderManager.print();
    // std::cout << "a" << std::endl;
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

  // Entities
  Entity a = entityManager.create();
  Entity b = entityManager.create();

  // REGISTER
  void attachManagers()
  {
    transformManager.add(
        a, TransformComponent{Vector2{0.0f, 0.0f},
                              Vector2{VIRTUAL_X / 2.0, VIRTUAL_Y / 2.0},
                              Vector2{10.0f, 10.0f}, 0.0f});
    transformManager.add(b, TransformComponent{Vector2{0.5f, 0.5f},
                                               Vector2{0.0, 0.0f},
                                               Vector2{10.0f, 10.0f}, 0.0f});

    renderManager.add(a, {true, {1.0f, 0.0f, 0.0f, 1.0f}});
    renderManager.add(b, {true, {0.0f, 1.0f, 0.0f, 1.0f}});
  }

  void load() { attachManagers(); }

  // GAMELOOP UPDATA
  void update(float dt)
  {
    renderSystem.renderManager.print();
    renderSystem.draw();
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
