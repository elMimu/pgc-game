#pragma once
#include "engine/core/Types.hpp"
#include "engine/scene/Scene.hpp"
#include "raylib.h"
#include <vector>

class GameplayScene : public Scene
{
public:
  GameplayScene(World &world) : Scene(world) {};
  int screenX = 360;
  int screenY = 640;
  int widthPadding = 5;

  float w = 1.0f / 4.0f;
  float h = 1.0f / 5.0f;

  std::vector<Entity> leftBoxItems;
  std::vector<Entity> rightBoxItems;

  Entity leftBox;
  Entity rightBox;

  void constructBoxes();
  void inputHandler();
  void onLoad();

  std::vector<Entity> buildBoxItems(int items, Entity parent);
  Entity createBoxItem(Vector2 position, Entity parent, float aspect);
  void createTitle();
  std::vector<Vector2> mapItemsPosition(int items);
  std::vector<Vector2> mapEvenItemsPosition(int items);
  std::vector<Vector2> mapOddItemsPosition(int items);
};
