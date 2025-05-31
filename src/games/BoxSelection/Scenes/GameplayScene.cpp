
#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/Types.hpp"
#include "engine/render/RenderTextSystem.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "raylib.h"
#include <vector>

void GameplayScene::onLoad()
{
  createTitle();
  constructBoxes();
}

void GameplayScene::constructBoxes()
{
  // left box
  leftBox = world.entityManager.create();
  rightBox = world.entityManager.create();

  // attach components
  world.attach<Transformable>(
      leftBox,
      Transformable({0.5f, 0.5f}, {0.25f * screenX, 0.6f * screenY},
                    {0.5f * screenX - widthPadding, 0.5f * screenY}, 0.0f));
  world.attach<RenderRectangle>(leftBox, RenderRectangle({0, BLUE}));
  world.attach<GlobalTransformable>(leftBox, {});

  leftBoxItems = buildBoxItems(9, leftBox);

  world.attach<Transformable>(
      rightBox,
      Transformable({0.5f, 0.5f}, {0.75f * screenX, 0.6f * screenY},
                    {0.5f * screenX - widthPadding, 0.5f * screenY}, 0.0f));
  world.attach<GlobalTransformable>(rightBox, {});
  world.attach<RenderRectangle>(rightBox, RenderRectangle({0, BLUE}));

  rightBoxItems = buildBoxItems(10, rightBox);
}

void GameplayScene::createTitle()
{
  Entity titleText = world.entityManager.create();
  world.attach<Transformable>(
      titleText, Transformable({0.5f, 0.5f}, {0.468f * screenX, 0.1f * screenY},
                               {1.0f * screenX, 1.0f}, 0.0f, 0));
  world.attach<GlobalTransformable>(titleText, {});
  // world.attach<RenderRectangle>(titleText, RenderRectangle({5, GREEN}));
  world.attach<RenderText>(titleText,
                           RenderText("Clique na caixa com mais items",
                                      world.fontLoader.get("chewy"), 1, 1.0f,
                                      WHITE, 5, 0));
}

std::vector<Entity> GameplayScene::buildBoxItems(int items, Entity parent)
{
  std::vector<Vector2> positions = mapItemsPosition(items);
  std::vector<Entity> entities;

  float aspect = TransformUtils::getAspect(parent, world);

  for (auto pos : positions)
  {
    entities.push_back(createBoxItem(pos, parent, aspect));
  }

  return entities;
}

Entity GameplayScene::createBoxItem(Vector2 position, Entity parent,
                                    float aspect)
{

  Entity newEntity = world.entityManager.create();

  world.attach<Transformable>(
      newEntity, Transformable({0.5f, 0.5f}, position,
                               {0.95f * w, 0.95f * w * aspect}, 0.0f, parent));

  world.attach<RenderRectangle>(newEntity, RenderRectangle({1, MAGENTA}));

  world.attach<GlobalTransformable>(newEntity, {});

  return newEntity;
}

std::vector<Vector2> GameplayScene::mapEvenItemsPosition(int items)
{
  switch (items)
  {
  case 2:
    return {
        {0.5f - w / 2.0f, 0.5f},
        {0.5f + w / 2.0f, 0.5f},
    };
  case 4:
    return {
        {0.5f - w / 2.0f, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f, 0.5f + h / 2.0f},
        {0.5f + w / 2.0f, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f, 0.5f + h / 2.0f},
    };
  case 6:
    return {
        {0.5f - w / 2.0f, 0.5f - h}, {0.5f - w / 2.0f, 0.5f + h},
        {0.5f - w / 2.0f, 0.5f},     {0.5f + w / 2.0f, 0.5f},
        {0.5f + w / 2.0f, 0.5f - h}, {0.5f + w / 2.0f, 0.5f + h},
    };
  case 8:
    return {
        {0.5f - w / 2.0f, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f - w, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f, 0.5f + h / 2.0f},
        {0.5f - w / 2.0f - w, 0.5f + h / 2.0f},

        {0.5f + w / 2.0f, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f + w, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f, 0.5f + h / 2.0f},
        {0.5f + w / 2.0f + w, 0.5f + h / 2.0f},
    };
  default:
    return {
        {0.5f - w / 2.0f, 0.5f - 2 * h}, {0.5f - w / 2.0f, 0.5f - h},
        {0.5f - w / 2.0f, 0.5f},         {0.5f - w / 2.0f, 0.5f + h},
        {0.5f - w / 2.0f, 0.5f + 2 * h},

        {0.5f + w / 2.0f, 0.5f - 2 * h}, {0.5f + w / 2.0f, 0.5f - h},
        {0.5f + w / 2.0f, 0.5f},         {0.5f + w / 2.0f, 0.5f + h},
        {0.5f + w / 2.0f, 0.5f + 2 * h},
    };
  }
};

std::vector<Vector2> GameplayScene::mapOddItemsPosition(int items)
{
  switch (items)
  {
  case 1:
    return {{0.5f, 0.5f}};
  case 3:
    return {{0.5f - w, 0.5f}, {0.5, 0.5}, {0.5f + w, 0.5f}};
  case 5:
    return {{0.5f - w, 0.5f - h},
            {0.5f - w, 0.5f + h},
            {0.5f, 0.5f},
            {0.5f + w, 0.5f - h},
            {0.5f + w, 0.5f + h}};
  case 7:
    return {{0.5f - w, 0.5f - h}, {0.5f - w, 0.5f + h}, {0.5f, 0.5f - h},
            {0.5f, 0.5f},         {0.5f, 0.5f + h},     {0.5f + w, 0.5f - h},
            {0.5f + w, 0.5f + h}};
  default:
    return {{0.5f - w, 0.5f - h}, {0.5f - w, 0.5f + h}, {0.5f, 0.5f - h},
            {0.5f - w, 0.5f},     {0.5f, 0.5f},         {0.5f + w, 0.5f},
            {0.5f, 0.5f + h},     {0.5f + w, 0.5f - h}, {0.5f + w, 0.5f + h}};
  };
};

std::vector<Vector2> GameplayScene::mapItemsPosition(int items)
{
  bool isEven = (items % 2) == 0;
  if (isEven)
  {
    return mapEvenItemsPosition(items);
  }
  return mapOddItemsPosition(items);
};

void GameplayScene::inputHandler() {};
