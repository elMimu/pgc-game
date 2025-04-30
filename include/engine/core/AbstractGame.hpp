#pragma once

#include "engine/core/IGame.hpp"

class AbstractGame : public IGame
{
public:
  AbstractGame(int x, int y) : virtualX(x), virtualY(y) {}
  int getVirtualX() const override { return virtualX; }
  int getVirtualY() const override { return virtualY; }

private:
  const int virtualX;
  const int virtualY;
};
