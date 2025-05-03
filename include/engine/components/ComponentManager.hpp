#pragma once

#include "engine/components/IComponentManager.hpp"
#include "engine/core/Types.hpp"
#include <iostream>
#include <unordered_map>

template <typename T> class ComponentManager : public IComponentManager
{
public:
  void add(Entity e, const T &component);
  void remove(Entity e) override;
  bool has(Entity e);
  T &getEntityComponent(Entity e);
  void printAttachedEntities();
  std::unordered_map<Entity, T> getManagerMap();

private:
  std::unordered_map<Entity, T> managerMap;
};

template <typename T>
std::unordered_map<Entity, T> ComponentManager<T>::getManagerMap()
{
  return managerMap;
}

template <typename T>
void ComponentManager<T>::add(Entity e, const T &component)
{
  // TODO - HANDLE EXCEPTION - KEY ALREADY EXISTS;
  managerMap.insert({e, component});
}

template <typename T> bool ComponentManager<T>::has(Entity e)
{
  return managerMap.find(e) != managerMap.end();
}

template <typename T> void ComponentManager<T>::remove(Entity e)
{
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  managerMap.erase(e);
}

template <typename T> T &ComponentManager<T>::getEntityComponent(Entity e)
{
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  return managerMap.at(e);
}

template <typename T> void ComponentManager<T>::printAttachedEntities()
{
  for (auto &[e, manager] : managerMap)
  {
    std::cout << e << "\n";
 }
}
