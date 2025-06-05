#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/feedbackTextFactory.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"

void FeedbackScene::onLoad() {
  auto &state = world.getUserState<GameState>();
  bool win = hasWon();

  setupCounting();

  Vector2 screen = world.getScreenCoord();

  showTextFeedback(win, screen.x, screen.y, [&]() {
    auto &itemBoxCounter = world.get<ItemBoxCounter>(state.leftBox);
    itemBoxCounter.start = true;
  });
}

void FeedbackScene::setupCounting() {
  auto &state = world.getUserState<GameState>();

  /*world.attach<ItemBoxCounter>(state.leftBox,*/
  /*                             {state.leftBox, 1.0f, 1.0, []() {}});*/

  /*world.attach<ItemBoxCounter>(state.rightBox,*/
  /*                             {state.rightBox, 1.0f, 1.0f, []() {}});*/
}

void FeedbackScene::showTextFeedback(bool win, float screenX, float screenY,
                                     std::function<void()> callback) {
  std::string text = "Que pena!";
  Color color = RED;

  if (win) {
    text = "Muito bem!";
    color = GREEN;
  }

  tfb = FeedbackTextFactory::create(
      world,
      Transformable({0.5, 0.5}, {0.5f * screenX, 0.5f * screenY}, {0.0f, 0.0f},
                    0.0f),
      Visual(color, 3), RenderText(text, world.fontLoader.get("chewy")),
      FloatOut({screenX * 0.5f, screenY * 0.4f},
               {screenX * 0.5f, screenY * 0.1f}, {0.0f, 0.0f},
               {screenX * 0.6f, screenY * 1.0f}, 1.0f, Easing::easeOutBounce,
               callback));

  world.get<FloatOut>(tfb).play = true;
}

bool FeedbackScene::hasWon() {
  auto &state = world.getUserState<GameState>();

  return (state.userChoice == state.correctChoice);
}

void FeedbackScene::inputHandler() {}
