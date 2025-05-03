#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/entity/EntityManager.hpp"
#include "engine/render/RenderRegistry.hpp"

// FORWARD DECLARATION
class IGame;

class Engine
{
public:
  EntityManager entityManager;
  ComponentRegistry componentRegistry;
  void run(IGame &game);
};
