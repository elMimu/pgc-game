#pragma once

#include "../entity/EntityManager.cpp"
#include <unordered_map>

template <typename T> class ComponentManager
{
public:
  std::unordered_map<EntityManager::Entity, T> all;

  void add(EntityManager::Entity e, const T &component)
  {
    all.insert({e, component});
  }

  bool has(EntityManager::Entity e) { all.find(e) != all.end(); }

  void remove(EntityManager::Entity e)
  {
    if (!all.find(e))
    {
      return;
    }
    all.erase(e);
  }

  T &get(EntityManager::Entity e) { return all.at(e); }
  std::unordered_map<EntityManager::Entity, T> &getAll() { return all; }

  void print()
  {
    for (auto &[e, _] : getAll())
    {
      std::cout << e << std::endl;
    }
  }
};
