#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/feedbackTextFactory.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"

void FeedbackScene::onLoad() {
  auto &state = world.getUserState<GameState>();
  bool win = hasWon();

  Vector2 screen = world.getScreenCoord();

  // dialogue
  Entity dialogueBox = world.entityManager.create();
  world.attach<Transformable>(dialogueBox, {{0.5f, 0.5f},
                                            {0.5f * screen.x, 0.2f * screen.y},
                                            {0.8f * screen.x, 0.05f * screen.y},
                                            0.0f});
  world.attach<GlobalTransformable>(dialogueBox, {});
  world.attach<Visual>(dialogueBox, {BLUE, 2});
  world.attach<RenderRectangle>(dialogueBox, {});

  Entity dialogue = world.entityManager.create();
  world.attach<Transformable>(
      dialogue, {{0.5f, 0.5f}, {0.5f, 0.5f}, {0.9f, 0.15f}, 0.0f, dialogueBox});
  world.attach<GlobalTransformable>(dialogue, {});
  world.attach<Visual>(dialogue, {WHITE, 3});
  world.attach<RenderText>(dialogue, {"Vamos contar os items de cada caixa.",
                                      world.fontLoader.get("chewy")});
  // setup counters
  //
  Entity lCounterBox = world.entityManager.create();
  world.attach<Transformable>(
      lCounterBox,
      {{0.5f, 1.0f},
       {0.5f, -0.02f},
       {0.3f, 0.3f * TransformUtils::getAspect(state.leftBox, world)},
       0.0f,
       state.leftBox});
  world.attach<GlobalTransformable>(lCounterBox, {});
  world.attach<Visual>(lCounterBox, {BLUE, 2});
  world.attach<RenderRectangle>(lCounterBox, {});

  std::cout << TransformUtils::getAspect(state.leftBox, world) << "\n";

  // showTextFeedback(win, screen.x, screen.y,
  //                  [&]()
  //                  {
  //                    auto &itemBoxCounter =
  //                        world.get<ItemBoxCounter>(state.leftBox);
  //                    itemBoxCounter.start = true;
  //                  });
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
