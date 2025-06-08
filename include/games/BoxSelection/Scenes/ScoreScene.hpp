#pragma once

#include "engine/scene/Scene.hpp"

class ScoreScene : public Scene {
public:
  ScoreScene(World &world) : Scene(world) {}

  void inputHandler() override;
  void onLoad() override;
  void onUpdate(float dt) override;
  void onFinish() override;
};
