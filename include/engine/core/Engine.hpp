#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/entity/EntityManager.hpp"
// FORWARD DECLARATION
class IGame;

class Engine
{
public:
  EntityManager entityManager;
  ComponentRegistry componentRegistry;
  void run(IGame &game);
};
