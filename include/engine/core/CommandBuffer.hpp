#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/core/Types.hpp"
#include "engine/entity/EntityManager.hpp"
#include <typeindex>
#include <utility>
#include <vector>

class CommandBuffer {
public:
  void destroy(Entity e) { toDestroy.push_back(e); }

  void dettach(Entity e, std::type_index t) { toDettach.push_back({e, t}); }

  void dettachAll(Entity e) { toDettachAll.push_back(e); }

  void flush(EntityManager &manager, ComponentRegistry &registry) {
    for (auto [e, t] : toDettach) {
      registry.dettachComponent(e, t);
    }

    for (auto e : toDettachAll) {
      registry.dettachFromAllManagers(e);
    }

    for (auto e : toDestroy) {
      manager.destroy(e);
    }

    toDestroy.clear();
    toDettach.clear();
    toDettachAll.clear();
  }

private:
  std::vector<Entity> toDestroy;
  std::vector<Entity> toDettachAll;
  std::vector<std::pair<Entity, std::type_index>> toDettach;
};
