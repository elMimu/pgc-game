#pragma once

#include "engine/entity/EntityManager.hpp"
#include <iostream>
#include <unordered_map>
template <typename T> class ComponentManager
{
public:
  void add(EntityManager::Entity e, const T &component);
  bool has(EntityManager::Entity e);
  void destroy(EntityManager::Entity e);
  T &getEntityComponent(EntityManager::Entity e);
  void printAttachedEntities();

private:
  std::unordered_map<EntityManager::Entity, T> allManagers;
};

template <typename T>
void ComponentManager<T>::add(EntityManager::Entity e, const T &component)
{
  // TODO - HANDLE EXCEPTION - KEY ALREADY EXISTS;
  allManagers.insert({e, component});
}

template <typename T> bool ComponentManager<T>::has(EntityManager::Entity e)
{
  return allManagers.find(e) != allManagers.end();
}

template <typename T> void ComponentManager<T>::destroy(EntityManager::Entity e)
{
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  allManagers.erase(e);
}

template <typename T>
T &ComponentManager<T>::getEntityComponent(EntityManager::Entity e)
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
