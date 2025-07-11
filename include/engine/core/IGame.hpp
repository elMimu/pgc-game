#pragma once

class Engine;

class IGame
{
public:
  IGame() = default;
  virtual ~IGame() = default;
  virtual void load(Engine &engine) = 0;
  virtual int getVirtualX() const = 0;
  virtual int getVirtualY() const = 0;
};
