#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/entity/EntityManager.hpp"
#include "engine/render/RenderSystemRegistry.hpp"

// FORWARD DECLARATION
class IGame;

class Engine
{
public:
  EntityManager entityManager;
  ComponentRegistry componentRegistry;
  RenderSystemRegistry renderSystemRegistry;

  void run(IGame &game);
};
