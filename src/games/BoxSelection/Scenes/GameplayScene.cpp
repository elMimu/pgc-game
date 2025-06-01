#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderText.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/Types.hpp"
#include "games/BoxSelection/itemBoxFactory.hpp"
#include "raylib.h"

void GameplayScene::onLoad()
{
  createTitle();
  constructBoxes();
}

void GameplayScene::constructBoxes()
{
  leftBox = itemBoxFactory::createItemBox(
      world, 9, {0.5f, 0.5f}, {0.25f * screenX, 0.6f * screenY},
      {0.5f * screenX - widthPadding, 0.5f * screenY}, 0.0f, 0, BLUE, MAGENTA);

  rightBox = itemBoxFactory::createItemBox(
      world, 10, {0.5f, 0.5f}, {0.75f * screenX, 0.6f * screenY},
      {0.5f * screenX - widthPadding, 0.5f * screenY}, 0.0f, 0, BLUE, MAGENTA);
}

void GameplayScene::createTitle()
{
  Entity titleText = world.entityManager.create();
  world.attach<Transformable>(
      titleText, Transformable({0.5f, 0.5f}, {0.5f * screenX, 0.1f * screenY},
                               {1.0f * screenX, 1.0f}, 0.0f, 0));
  world.attach<GlobalTransformable>(titleText, {});

  world.attach<RenderText>(titleText,
                           RenderText("Clique na caixa com mais items",
                                      world.fontLoader.get("chewy"), WHITE, 5));
}

void GameplayScene::inputHandler() {};
