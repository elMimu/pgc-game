#pragma once

#include "engine/components/IComponentManager.hpp"
#include "engine/core/Types.hpp"
#include <iostream>
#include <unordered_map>

template <typename T> class ComponentManager : public IComponentManager {
public:
  T &attach(Entity e, const T &component);
  T &getComponent(Entity e);
  void remove(Entity e) override;
  bool has(Entity e) override;
  int size() override;
  void printAttachedEntities();

  std::unordered_map<Entity, T> &getAll();

private:
  std::unordered_map<Entity, T> managerMap;
};

template <typename T>
std::unordered_map<Entity, T> &ComponentManager<T>::getAll() {
  return managerMap;
}

template <typename T>
T &ComponentManager<T>::attach(Entity e, const T &component) {
  auto [iter, inserted] = managerMap.insert({e, component});
  if (!inserted) {
    // TODO - HANDLE EXCEPTION - KEY ALREADY EXISTS;
  }
  return iter->second;
}

template <typename T> bool ComponentManager<T>::has(Entity e) {
  return managerMap.find(e) != managerMap.end();
}

template <typename T> void ComponentManager<T>::remove(Entity e) {
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  if (managerMap.find(e) == managerMap.end()) {
    return;
  }
  managerMap.erase(e);
}

template <typename T> T &ComponentManager<T>::getComponent(Entity e) {
  // TODO - HANDLE EXCEPTION - NOT FOUND;
  return managerMap.at(e);
}

template <typename T> void ComponentManager<T>::printAttachedEntities() {
  for (auto &[e, manager] : managerMap) {
    std::cout << e << "\n";
  }
}

template <typename T> int ComponentManager<T>::size() {
  return managerMap.size();
}
