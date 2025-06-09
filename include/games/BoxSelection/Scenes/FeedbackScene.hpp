#pragma once

#include "engine/scene/Scene.hpp"
#include <string>

class FeedbackScene : public Scene {
public:
  enum Action {
    IDLE,
    SHOW_TEXT_FEEDBACK,
    POP_IN_FIRST_DIALOG,
    POP_IN_COUNTERS,
    START_COUNTING,
    POP_OUT_DIALOG,
    POP_IN_NEW_DIALOG,
    WAIT,
    POP_OUT_ALL_INFO,
  };

  Action action = Action::IDLE;

  float waitOnResult = 3.0f;

  Entity textFeedback;
  Entity dialogueBox;
  Entity dialogue;

  Entity lCounterBox;
  Entity lCounterText;
  Entity rCounterBox;
  Entity rCounterText;

  FeedbackScene(World &world) : Scene(world) {}
  void onLoad() override;
  void inputHandler() override;
  bool hasWon();

  Entity createCounterBox(Entity parent);
  Entity createCounterText(Entity parent);
  Entity createDialogue(std::string);
  Entity createTextFeedback();
  Entity createDialogueBox();
  std::string getTextFromInt(int n);

  void setupCounting();
  void onUpdate(float dt) override;
  void onFinish() override;
};
