#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/components/ScaleLerp.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/constants.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"
#include <algorithm>
#include <cmath>
#include <string>

void FeedbackScene::onLoad() {
  auto &state = world.getUserState<GameState>();

  textFeedback = createTextFeedback();

  dialogueBox = createDialogueBox();
  dialogue = createDialogue("Vamos contar os items de cada caixa.");

  lCounterBox = createCounterBox(state.leftBox);
  lCounterText = createCounterText(lCounterBox);

  rCounterBox = createCounterBox(state.rightBox);
  rCounterText = createCounterText(rCounterBox);

  action = SHOW_TEXT_FEEDBACK;
}

void FeedbackScene::onUpdate(float dt) {
  if (action == IDLE) {
    return;
  }

  if (action == SHOW_TEXT_FEEDBACK) {
    auto &floatAnim = world.get<FloatOut>(textFeedback);
    auto &state = world.getUserState<GameState>();
    floatAnim.callback = [this, &state]() {
      if (state.userChoice == state.correctChoice) {
        this->action = IDLE;
        addRequest(SceneRequest::Action::RELOAD);
      }
      this->action = POP_IN_FIRST_DIALOG;
    };
    floatAnim.play = true;
    action = IDLE;
  }

  if (action == POP_IN_FIRST_DIALOG) {
    auto &popAnim = world.get<ScaleLerp>(dialogueBox);
    auto [screenX, screenY] = world.getScreenCoord();
    popAnim.speed = constants::popSpeed;
    popAnim.easing = Easing::easeInQuad;
    popAnim.callback = [this]() { this->action = POP_IN_COUNTERS; };
    popAnim.to = {0.9f * screenX, 0.1f * screenY};
    action = IDLE;
  }

  if (action == POP_IN_COUNTERS) {
    /*{0.3f, 0.3f * TransformUtils::getAspect(parent, world)},*/
    auto &state = world.getUserState<GameState>();
    auto &leftPopAnim = world.get<ScaleLerp>(lCounterBox);
    auto &rightPopAnim = world.get<ScaleLerp>(rCounterBox);
    /**/
    leftPopAnim.speed = constants::popSpeed;
    leftPopAnim.easing = Easing::easeInQuad;
    leftPopAnim.to = {0.3f,
                      0.3f * TransformUtils::getAspect(state.leftBox, world)};
    rightPopAnim.speed = constants::popSpeed;
    rightPopAnim.easing = Easing::easeInQuad;
    rightPopAnim.callback = [this]() { this->action = START_COUNTING; };
    rightPopAnim.to = {0.3f,
                       0.3f * TransformUtils::getAspect(state.rightBox, world)};

    action = IDLE;
  }

  if (action == START_COUNTING) {
    auto &state = world.getUserState<GameState>();
    auto &lText = world.get<RenderText>(lCounterText);
    auto &rText = world.get<RenderText>(rCounterText);

    auto &lCount = world.get<ItemBoxCounter>(state.leftBox);
    auto &rCount = world.get<ItemBoxCounter>(state.rightBox);

    lCount.onCount = [&lText, &lCount, this]() {
      lText.text = getTextFromInt(lCount.count);
    };

    rCount.onCount = [&rText, &rCount, this]() {
      rText.text = getTextFromInt(rCount.count);
    };

    lCount.onFinish = [&rCount]() {
      rCount.timeElapsed = 1.0f;
      rCount.start = true;
    };
    rCount.onFinish = [this]() { this->action = POP_OUT_DIALOG; };

    lCount.start = true;

    action = IDLE;
  }

  if (action == POP_OUT_DIALOG) {
    auto &state = world.getUserState<GameState>();
    auto &dialogBoxScale = world.get<ScaleLerp>(dialogueBox);
    auto &dialogueText = world.get<RenderText>(dialogue);
    Vector2 tmp = dialogBoxScale.from;

    dialogBoxScale.to = {0.0f, 0.0f};
    dialogBoxScale.callback = [this]() { this->action = POP_IN_NEW_DIALOG; };

    action = IDLE;
  }

  if (action == POP_IN_NEW_DIALOG) {
    auto [screenX, screenY] = world.getScreenCoord();
    Vector2 to = {0.9f * screenX, 0.1f * screenY};
    auto &state = world.getUserState<GameState>();
    auto &dialogBoxScale = world.get<ScaleLerp>(dialogueBox);
    auto &dialogueText = world.get<RenderText>(dialogue);

    dialogueText.text =
        "A caixa com mais items possui " + std::to_string(state.correctChoice);
    dialogBoxScale.to = to;
    dialogBoxScale.callback = [this]() { this->action = WAIT; };

    action = IDLE;
  }

  if (action == WAIT) {
    waitOnResult = std::clamp(waitOnResult - dt, 0.0f, waitOnResult);
    if (waitOnResult <= 0) {
      action = POP_OUT_ALL_INFO;
    }
  }

  if (action == POP_OUT_ALL_INFO) {
    static int popOuted = 0;
    auto &dialogBoxScale = world.get<ScaleLerp>(dialogueBox);
    auto &lCounterBoxScale = world.get<ScaleLerp>(lCounterBox);
    auto &rCounterBoxScale = world.get<ScaleLerp>(rCounterBox);

    Vector2 zero = {0.0f, 0.0f};

    dialogBoxScale.callback = [this]() {};

    lCounterBoxScale.callback = [this]() {};

    rCounterBoxScale.callback = [this]() {
      addRequest(SceneRequest::Action::RELOAD);
    };

    dialogBoxScale.to = zero;
    lCounterBoxScale.to = zero;
    rCounterBoxScale.to = zero;

    action = IDLE;
  }
}

void FeedbackScene::onFinish() {
  world.dettachFromAll(lCounterText);
  world.dettachFromAll(lCounterBox);
  world.destroy(lCounterText);
  world.destroy(lCounterBox);
  world.dettachFromAll(rCounterText);
  world.dettachFromAll(rCounterBox);
  world.destroy(rCounterText);
  world.destroy(rCounterBox);
}

Entity FeedbackScene::createCounterBox(Entity parent) {
  auto &state = world.getUserState<GameState>();
  auto &parentT = world.get<Transformable>(parent);

  Entity counterBox = world.entityManager.create();
  world.attach<Transformable>(
      counterBox, {{0.5f, 0.5f},
                   {0.5f, -0.12f},
                   {0.0f, 0.0f},
                   /*{0.3f, 0.3f * TransformUtils::getAspect(parent, world)},*/
                   0.0f,
                   parent});
  world.attach<GlobalTransformable>(counterBox, {});
  world.attach<Visual>(counterBox, {BLUE, 2});
  world.attach<RenderRectangle>(counterBox, {});
  world.attach<ScaleLerp>(counterBox, {0.0f, 0.0f});

  return counterBox;
}

Entity FeedbackScene::createCounterText(Entity parent) {
  Entity counterText = world.entityManager.create();
  world.attach<Transformable>(
      counterText, {{0.5f, 0.5f}, {0.5f, 0.5f}, {0.6f, 1.0f}, 0.0f, parent});
  world.attach<GlobalTransformable>(counterText, {});
  world.attach<Visual>(counterText, {WHITE, 3});
  world.attach<RenderText>(counterText,
                           {"00", world.fontLoader.get(constants::primFont)});

  return counterText;
}

Entity FeedbackScene::createDialogue(std::string text) {
  Entity dialogue = world.entityManager.create();
  world.attach<Transformable>(
      dialogue, {{0.5f, 0.5f}, {0.5f, 0.5f}, {0.9f, 1.0f}, 0.0f, dialogueBox});
  world.attach<GlobalTransformable>(dialogue, {});
  world.attach<Visual>(dialogue, {WHITE, 3});
  world.attach<RenderText>(dialogue,
                           {text, world.fontLoader.get(constants::primFont)});

  return dialogue;
}

Entity FeedbackScene::createDialogueBox() {
  auto [screenX, screenY] = world.getScreenCoord();
  dialogueBox = world.entityManager.create();
  world.attach<Transformable>(
      dialogueBox,
      {{0.5f, 0.5f}, {0.5f * screenX, 0.18f * screenY}, {0.0f, 0.0f}, 0.0f});
  world.attach<GlobalTransformable>(dialogueBox, {});
  world.attach<Visual>(dialogueBox, {BLUE, 2});
  world.attach<RenderRectangle>(dialogueBox, {});
  world.attach<ScaleLerp>(dialogueBox, {{0.0f, 0.0f}});

  return dialogueBox;
}

Entity FeedbackScene::createTextFeedback() {
  bool win = hasWon();
  std::string text = win ? "Muito Bem" : "Que Pena!";
  Color color = win ? GREEN : RED;
  auto [screenX, screenY] = world.getScreenCoord();

  Entity textFeedback = world.entityManager.create();
  world.attach<Transformable>(
      textFeedback, Transformable({0.5, 0.5}, {0.5f * screenX, 0.5f * screenY},
                                  {0.0f, 0.0f}, 0.0f));
  world.attach<GlobalTransformable>(textFeedback, {});
  world.attach<Visual>(textFeedback, {color, 5});
  world.attach<RenderText>(textFeedback,
                           {text, world.fontLoader.get(constants::primFont)});
  world.attach<FloatOut>(
      textFeedback, FloatOut({screenX * 0.5f, screenY * 0.5f},
                             {screenX * 0.5f, screenY * 0.2f}, {0.0f, 0.0f},
                             {screenX * 0.6f, screenY * 1.0f}, 1.0f,
                             Easing::easeOutBounce, []() {}));
  return textFeedback;
}

bool FeedbackScene::hasWon() {
  auto &state = world.getUserState<GameState>();

  return (state.userChoice == state.correctChoice);
}

std::string FeedbackScene::getTextFromInt(int n) {
  if (n / 10 == 0) {
    return "0" + std::to_string(n);
  }
  return std::to_string(n);
}

void FeedbackScene::inputHandler() {}
