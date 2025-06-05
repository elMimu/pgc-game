#pragma once

#include "engine/scene/Scene.hpp"

class FeedbackScene : public Scene {
public:
  Entity tfb;
  FeedbackScene(World &world) : Scene(world) {}
  void onLoad() override;
  void inputHandler() override;
  bool hasWon();
  void showTextFeedback(bool win, float screenX, float screenY,
                        std::function<void()> callback);
  void setupCounting();
};
