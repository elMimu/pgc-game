#include "engine/entity/EntityManager.hpp"
#include <iostream>

EntityManager::Entity EntityManager::create()
{
  Entity id = nextId++;
  if (nextId >= ENTITY_MAX)
  {
    // TODO - EXCEPTION HANDLING
    std::cout << "ENTITY MAXIMUM REACHED" << "\n";
    return ENTITY_MAX;
  }
  allEntities.insert(id);
  return id;
};

void EntityManager::destroy(Entity toDelete)
{
  allEntities.erase(toDelete);
}

// SHOULD BE PART OF A VERBOSE FLAG
void EntityManager::print()
{
  for (auto &e : allEntities)
  {
    std::cout << e << "\n";
  }
}
