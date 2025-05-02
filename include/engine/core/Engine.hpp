#pragma once

#include "engine/entity/EntityManager.hpp"
// FORWARD DECLARATION
class IGame;

class Engine
{
public:
  EntityManager entityManager;
  void run(IGame &game);
};
