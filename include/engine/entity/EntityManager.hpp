#pragma once

#include <cstdint>
#include <set>

class EntityManager
{
public:
  using Entity = uint32_t;
  static constexpr Entity ENTITY_MAX = 500;

  Entity create();
  void destroy(Entity toDelete);
  void print();

private:
  Entity nextId = 0;
  std::set<Entity> allEntities;
};
