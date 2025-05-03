#pragma once

#include "engine/entity/EntityManager.hpp"
#include <iostream>
#include <unordered_map>
template <typename T> class ComponentManager
{
public:
  void add(Entity e, const T &component);
  bool has(Entity e);
  void destroy(Entity e);
  T &getEntityComponent(Entity e);
  void printAttachedEntities();

private:
  std::unordered_map<Entity, T> allManagers;
};

template <typename T>
void ComponentManager<T>::add(Entity e, const T &component)
{
  // TODO - HANDLE EXCEPTION - KEY ALREADY EXISTS;
  allManagers.insert({e, component});
}

template <typename T> bool ComponentManager<T>::has(Entity e)
{
  return allManagers.find(e) != allManagers.end();
}

template <typename T> void ComponentManager<T>::destroy(Entity e)
{
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  allManagers.erase(e);
}

template <typename T> T &ComponentManager<T>::getEntityComponent(Entity e)
{
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  return allManagers.at(e);
}

template <typename T> void ComponentManager<T>::printAttachedEntities()
{
  for (auto &[e, manager] : allManagers)
  {
    std::cout << e << "\n";
  }
}
