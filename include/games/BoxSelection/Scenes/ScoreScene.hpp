#pragma once

#include "engine/scene/Scene.hpp"

class ScoreScene : public Scene {
public:
  ScoreScene(World &world) : Scene(world) {}
  enum Action { IDLE, POP_IN_SCORE };
  Action action = IDLE;

  std::string getScoreString(float number);
  void inputHandler() override;
  void onLoad() override;
  void onUpdate(float dt) override;
  void onFinish() override;

  Entity messageBox;
};
