#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/core/Types.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "engine/utils/Random.hpp"
#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "games/BoxSelection/clickableBoxFactory.hpp"
#include "games/BoxSelection/components/ScaleLerp.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"

void GameplayScene::onLoad() {
  // update GameState
  auto &gameState = world.getUserState<GameState>();
  int leftQtd = getRandomInt(1, 10);
  int rightQtd = leftQtd;

  while (rightQtd == leftQtd) {
    rightQtd = getRandomInt(1, 10);
  }

  gameState.correctChoice = leftQtd > rightQtd ? leftQtd : rightQtd;

  leftBox = ClickableBoxFactory::creatClickableBox(
      world, leftQtd, {0.5f, 0.5f}, {0.25f * screenX, 0.6f * screenY},
      {0.0, 0.0f}, 0.0f, 0, BLUE, MAGENTA,
      [&gameState, leftQtd](Entity e) { gameState.userChoice = leftQtd; });

  rightBox = ClickableBoxFactory::creatClickableBox(
      world, rightQtd, {0.5f, 0.5f}, {0.75f * screenX, 0.6f * screenY},
      {0.0f, 0.0f}, 0.0f, 0, BLUE, MAGENTA,
      [&gameState, rightQtd](Entity e) { gameState.userChoice = rightQtd; });

  gameState.leftBox = leftBox;
  gameState.rightBox = rightBox;

  createTitle();

  action = POP_BOXES;
}

void GameplayScene::createTitle() {
  Entity titleText = world.entityManager.create();
  world.attach<Transformable>(
      titleText, Transformable({0.5f, 0.5f}, {0.5f * screenX, 0.05f * screenY},
                               {0.8f * screenX, 1.0f}, 0.0f, 0));
  world.attach<GlobalTransformable>(titleText, {});
  world.attach<Visual>(titleText, {});

  world.attach<RenderText>(titleText,
                           RenderText("Clique na caixa com mais items",
                                      world.fontLoader.get("chewy")));
}

void GameplayScene::onUpdate(float dt) {
  if (action == IDLE) {
    return;
  }

  if (action == POP_BOXES) {
    world.attach<ScaleLerp>(leftBox,
                            {0.5f * screenX - widthPadding, 0.5f * screenY});
    world.attach<ScaleLerp>(rightBox,
                            {{0.5f * screenX - widthPadding, 0.5f * screenY},
                             1.0f,
                             [this]() { action = GAME; }});
    action = IDLE;
  }

  if (action == GAME) {
    auto &state = world.getUserState<GameState>();
    if (state.userChoice != 0) {
      addRequest<FeedbackScene>(SceneRequest::Action::PUSH);
      action = IDLE;
    }
  }

  if (action == POP_OUT_BOXES) {
    std::cout << "abc\n";
    auto &lBoxScale = world.get<ScaleLerp>(leftBox);
    lBoxScale.to = {0.0f, 0.0f};
    auto &rBoxScale = world.get<ScaleLerp>(rightBox);
    rBoxScale.to = {0.0f, 0.0f};
    rBoxScale.callback = [this]() { action = DESTROY_BOXES; };

    action = IDLE;
  }

  if (action == DESTROY_BOXES) {
    auto entities = world.entityManager.getAll();
    for (auto e : entities) {
      auto &t = world.get<Transformable>(e);
      if (t.parent == leftBox || t.parent == rightBox) {
        world.dettachFromAll(e);
        world.destroy(e);
      }
    }

    world.dettachFromAll(leftBox);
    world.destroy(leftBox);
    world.dettachFromAll(rightBox);
    world.destroy(rightBox);

    isLoaded = false;

    action = IDLE;
  }
}

void GameplayScene::clearBox(Entity e) {};

void GameplayScene::onFinish() { std::cout << "Game Over\n"; }

void GameplayScene::onReload() {
  // Reset game state
  auto &state = world.getUserState<GameState>();
  state.userChoice = 0;
  state.correctChoice = 0;

  std::cout << "bigger\n";

  action = POP_OUT_BOXES;

  // Destroy scene entities
  /*auto entities = world.entityManager.getAll();*/
  /*for (auto e : entities) {*/
  /*  auto &t = world.get<Transformable>(e);*/
  /*  if (t.parent == leftBox || t.parent == rightBox) {*/
  /*    world.dettachFromAll(e);*/
  /*    world.destroy(e);*/
  /*  }*/
  /*}*/

  /*world.dettachFromAll(leftBox);*/
  /*world.destroy(leftBox);*/
  /*world.dettachFromAll(rightBox);*/
  /*world.destroy(rightBox);*/
}

void GameplayScene::inputHandler() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    auto &input = world.getUserState<InputState>();
    input.pointerPos = GetMousePosition();
    input.pointerDown = true;
    return;
  }

  if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
    auto &input = world.getUserState<InputState>();
    input.pointerDown = false;
    input.pointerReleased = true;
    return;
  }

  auto &input = world.getUserState<InputState>();
  input.pointerReleased = false;
  input.pointerDown = false;
};
