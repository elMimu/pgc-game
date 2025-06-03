#pragma once

#include "engine/scene/Scene.hpp"

class FeedbackScene : public Scene {
  public:
  FeedbackScene(World &world) : Scene(world) {}
  Entity fbt;
  void onLoad() override;
  void inputHandler() override;
};
