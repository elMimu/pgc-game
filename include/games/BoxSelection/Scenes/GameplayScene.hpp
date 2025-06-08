#pragma once
#include "engine/core/Types.hpp"
#include "engine/scene/Scene.hpp"

class GameplayScene : public Scene {
public:
  GameplayScene(World &world) : Scene(world) {};
  enum Action {
    IDLE,
    POP_BOXES,
    GAME,
    POP_OUT_BOXES,
    DESTROY_BOXES,
  };
  Action action = IDLE;
  int screenX = 360;
  int screenY = 640;
  int widthPadding = 5;

  float w = 1.0f / 5.0f;
  float h = 1.0f / 5.0f;

  Entity leftBox;
  Entity rightBox;

  Entity userChoice = 0;
  Entity correctChoice = 0;

  void constructBoxes();
  void inputHandler() override;
  void onLoad() override;
  void onUpdate(float dt) override;
  void onFinish() override;
  void onReload() override;
  void clearBox(Entity e);

  void createTitle();
};
