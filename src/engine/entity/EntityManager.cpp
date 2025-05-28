#include "engine/entity/EntityManager.hpp"
#include <iostream>

Entity EntityManager::create()
{
  Entity newId;

  if (!freeIds.empty())
  {
    newId = freeIds.front();
    freeIds.pop();
  }
  else if (nextId <= ENTITY_MAX)
  {
    newId = nextId++;
  }
  else
  {
    // HANDLE EXCEPTION - MAXIMUN ENTITY REACHED
    return ENTITY_MAX;
  }

  allEntities.insert(newId);
  return newId;
};

void EntityManager::destroy(Entity toDelete)
{
  freeIds.push(toDelete);
  allEntities.erase(toDelete);
}

// TODO - SHOULD BE PART OF A DEBUG
void EntityManager::print()
{
  for (auto &e : allEntities)
  {
    std::cout << e << "\n";
  }
}
