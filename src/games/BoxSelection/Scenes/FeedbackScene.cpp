#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/feedbackTextFactory.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"

void FeedbackScene::onLoad() {
  auto &state = world.getUserState<GameState>();
  std::string text = "Que pena!";
  Color color = RED;

  if (state.userChoice == state.correctChoice) {
    text = "Muito bem!";
    color = GREEN;
  }

  Vector2 screen = world.getScreenCoord();

  fbt = FeedbackTextFactory::create(
      world,
      Transformable({0.5, 0.5}, {0.5f * screen.x, 0.5f * screen.y},
                    {0.0f, 0.0f}, 0.0f),
      Visual(color, 3), RenderText(text, world.fontLoader.get("chewy")),
      FloatOut({screen.x * 0.5f, screen.y * 0.4f},
               {screen.x * 0.5f, screen.y * 0.1f}, {0.0f, 0.0f},
               {screen.x * 0.6f, screen.y * 1.0f}, 1.0f, Easing::easeOutBounce));

  /*world.get<FloatOut>(fbt).play = true;*/
}

void FeedbackScene::inputHandler() {
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    world.get<FloatOut>(fbt).play = true;
  }
}
