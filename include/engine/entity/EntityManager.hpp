#pragma once

#include "engine/core/Types.hpp"
#include <queue>
#include <set>

class EntityManager
{
public:
  static constexpr Entity ENTITY_MAX = 500;

  Entity create();
  void destroy(Entity toDelete);
  void print();

private:
  Entity nextId = 1;
  std::set<Entity> allEntities;
  std::queue<Entity> freeIds;
};
