#pragma once
#include "engine/components/ComponentManager.cpp"
#include "engine/components/RenderComponent.cpp"
#include "engine/components/TransformComponent.cpp"
#include "engine/entity/EntityManager.cpp"
#include "engine/scene/src/Scene.cpp"
#include "engine/scene/src/SceneManager.cpp"
#include "engine/systems/RenderSystem.cpp"
#include "raylib.h"
#include <iostream>
#include <ostream>

// DEFINING VIRTUAL RESOLUTION --------- //
#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// INTRO SCENE
class IntroScene : public Scene
{
public:
  void onLoad() { std::cout << "Intro Scene Loaded" << std::endl; };
  void onUpdate(float dt) {};
  void onFinish() { std::cout << "Intro Scene Finished" << std::endl; };
};

// SCENE_2
class GameplayScene : public Scene
{
public:
  void onLoad() { std::cout << "Gameplay Scene Loaded" << std::endl; };
  void onUpdate(float dt) {};
  void onFinish() { std::cout << "Gameplay Scene Finished" << std::endl; };
};
// SCENE_3
class EndScene : public Scene
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
    sceneManager.sceneStack.push_back(&endSCene);
    sceneManager.sceneStack.push_back(&gameplayScene);
    sceneManager.sceneStack.push_back(&introScene);
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
    sceneManager.update(dt);
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
