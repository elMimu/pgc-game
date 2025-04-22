#include "list"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

// DEFINING VIRTUAL RESOLUTION --------- //
#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// TRANSFORM OBJECT -------- //
class TransformProps
{
public:
  Vector2 position = {0.0f, 0.0f};
  Vector2 size = {1.0f, 1.0f};
  Vector2 origin = {0.5f, 0.5f};
  float rotation = 0.0f;
};

// SCENE OBJECT ---------- //
class Scene2DObject
{
public:
  std::string identifier = "";
  bool alive = true;
  TransformProps transform;
  Vector4 color;
  Scene2DObject *parent = nullptr;

  Scene2DObject() = default;

  void init(std::string identifier, Vector2 position = {0.0f, 0.0f},
            Vector2 size = {10.0f, 10.0f}, Vector2 origin = {0.5f, 0.5f},
            float rotation = 0.0f, Vector4 color = {1.0f, 1.0f, 1.0f, 1.0f})
  {
    this->identifier = identifier;
    transform.position = position;
    transform.size = size;
    transform.origin = origin;
    this->color = color;
  };

  TransformProps getWorldTransform(TransformProps current)
  {
    if (!parent)
    {
      return current;
    }

    TransformProps newTransform =
        calculateParenting(parent->transform, current);

    return parent->getWorldTransform(newTransform);
  }

  void draw()
  {
    TransformProps world = getWorldTransform(transform);
    DrawRectanglePro(Rectangle{world.position.x, world.position.y,
                               transform.size.x, transform.size.y},
                     Vector2{transform.size.x * transform.origin.x,
                             transform.size.y * transform.origin.y},
                     RAD2DEG * world.rotation, ColorFromNormalized(color));
  }

  void destroy() { alive = false; }

private:
  TransformProps calculateParenting(TransformProps p, TransformProps c)
  {
    TransformProps result;
    result.position = Vector2Add(p.position, c.position);
    result.rotation = p.rotation + c.rotation;
    result.size = c.size;
    return result;
  }
};

// SCENE --------- //
class Scene
{
public:
  std::unordered_map<std::string, Scene2DObject &> all;
  std::list<std::string> order;

  void add(Scene2DObject &obj)
  {
    // TODO add exception when same identifier
    order.push_back(obj.identifier);
    all.insert({obj.identifier, obj});
  };

  void draw()
  {
    auto it = order.begin();
    while (it != order.end())
    {
      auto found = all.find(*it);
      if (found != all.end() && found->second.alive)
      {
        found->second.draw();
        ++it;
      }
      else
      {
        all.erase(found->second.identifier);
        it = order.erase(it);
      }
    }
  }
};

// STATES --------- //

// STATE MACHINE ---------//

// MINIGAME ---------- //

// GAME STARTING POINT ---------- //
int main(void)
{

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(VIRTUAL_X, VIRTUAL_Y, "First Minigame");

  SetTargetFPS(60);

  // Create parent object
  Scene2DObject parent;
  parent.init("abc", {VIRTUAL_X / 2.0f, VIRTUAL_Y / 2.0f}, {60, 60},
              {0.5f, 0.5f}, 0.0f, {1, 0, 0, 1});

  // Create children
  Scene2DObject child1;
  child1.init("abcd", {80, 0}, {30, 30}, {0.5f, 0.5f}, 0.0f, {0, 1, 0, 1});
  child1.parent = &parent;

  Scene2DObject child2;
  child2.init("abcde", {-80, 0}, {30, 30}, {0.5f, 0.5f}, 0.0f, {0, 0, 1, 1});
  child2.parent = &parent;

  // Create Scene;
  Scene mainScene;

  mainScene.add(parent);
  mainScene.add(child1);
  mainScene.add(child2);

  bool once = true;
  while (!WindowShouldClose())
  {
    float time = GetTime();
    parent.transform.rotation = sinf(time) * 1.0f; // Oscillating rotation

    BeginDrawing();
    ClearBackground(DARKGRAY);

    mainScene.draw();
    if (time >= 10.0 && once)
    {
      once = false;
      child1.destroy();
      std::cout << child1.identifier << std::endl;
    }

    parent.draw();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
