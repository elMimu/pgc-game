#pragma once
#include "engine/core/Types.hpp"
#include "engine/scene/Scene.hpp"
#include "games/BoxSelection/gameState.hpp"

class GameplayScene : public Scene {
public:
  GameplayScene(World &world) : Scene(world) {};
  int screenX = 360;
  int screenY = 640;
  int widthPadding = 5;

  float w = 1.0f / 4.0f;
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

  void createTitle();
};
