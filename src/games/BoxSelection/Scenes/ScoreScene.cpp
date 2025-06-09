#include "games/BoxSelection/Scenes/ScoreScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "games/BoxSelection/components/ScaleLerp.hpp"
#include "games/BoxSelection/constants.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "raylib.h"
#include <iomanip>
#include <sstream>
#include <string>

void ScoreScene::inputHandler() {}

void ScoreScene::onLoad() {
  auto &state = world.getUserState<GameState>();

  auto [screenX, screenY] = world.getScreenCoord();

  messageBox = world.entityManager.create();
  world.attach<Transformable>(
      messageBox,
      {{0.5f, 0.5f}, {0.5f * screenX, 0.5f * screenY}, {0.0f, 0.0f}, 0.0f});
  world.attach<GlobalTransformable>(messageBox, {});
  world.attach<Visual>(messageBox, {BLUE, 1});
  world.attach<RenderRectangle>(messageBox, {});
  world.attach<ScaleLerp>(messageBox, {});

  Entity scoreTitleText = world.entityManager.create();
  world.attach<Transformable>(
      scoreTitleText,
      {{0.5f, 0.0f}, {0.5f, 0.0f}, {0.8f, 1.0f}, 0.0f, messageBox});
  world.attach<GlobalTransformable>(scoreTitleText, {});
  world.attach<Visual>(scoreTitleText, {WHITE, 2});
  world.attach<RenderText>(
      scoreTitleText,
      {"NOTA FINAL", world.fontLoader.get(constants::primFont)});

  Entity scoreText = world.entityManager.create();
  world.attach<Transformable>(
      scoreText, {{0.5f, 0.5f}, {0.5f, 0.6f}, {0.4f, 1.0f}, 0.0f, messageBox});

  world.attach<GlobalTransformable>(scoreText, {});
  world.attach<Visual>(scoreText, {WHITE, 2});
  world.attach<RenderText>(scoreText,
                           {getScoreString(state.score / (state.rounds * 0.1f)),
                            world.fontLoader.get(constants::primFont)});

  action = POP_IN_SCORE;
}

std::string ScoreScene::getScoreString(float number) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(0) << number;
  return oss.str();
}

void ScoreScene::onUpdate(float dt) {
  if (action == IDLE) {
    return;
  }

  if (action == POP_IN_SCORE) {
    auto [screenX, screenY] = world.getScreenCoord();
    auto &popAnim = world.get<ScaleLerp>(messageBox);
    popAnim.to = {0.4f * screenX, 0.4f * screenX};

    action = IDLE;
  }
}

void ScoreScene::onFinish() {}
