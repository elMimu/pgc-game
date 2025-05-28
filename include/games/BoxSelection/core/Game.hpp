#pragma once
#include "engine/core/AbstractGame.hpp"
#include "engine/core/Engine.hpp"

#define VIRTUAL_X 360
#define VIRTUAL_Y 640

class Game : public AbstractGame
{
public:
  Game() : AbstractGame(VIRTUAL_X, VIRTUAL_Y) {}
  void load(Engine &engine) override;
};
