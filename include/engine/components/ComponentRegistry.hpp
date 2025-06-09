#pragma once

#include "engine/components/ComponentManager.hpp"
#include "engine/components/IComponentManager.hpp"
#include "engine/core/MapRegistry.hpp"
#include "engine/core/Types.hpp"
#include <iostream>
#include <memory>
#include <stdexcept>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

class ComponentRegistry {
public:
  struct ComponentManagerNotFoundException : public std::runtime_error {
    ComponentManagerNotFoundException(const std::string type)
        : std::runtime_error("Manager for Component type '" + type +
                             "' not found.") {};
  };

  template <typename C> ComponentManager<C> &get() {
    std::type_index type = std::type_index(typeid(C));
    if (!isRegistered(type)) {
      throw ComponentManagerNotFoundException(typeid(C).name());
    }

    auto &managerPtrRef = allManagers.at(type);

    return dynamic_cast<ComponentManager<C> &>(*managerPtrRef);
  }

  bool isRegistered(std::type_index type) {
    if (allManagers.find(type) != allManagers.end()) {
      return true;
    }
    return false;
  }

  template <typename C> ComponentManager<C> &create() {
    std::type_index type = std::type_index(typeid(C));

    if (isRegistered(type)) {
      // TODO - HANDLE LOG - MANAGER EXISTS.
      std::cout << "Manager for Component" << type.name() << "already created."
                << "\n";
    }

    auto itemPtr = std::make_unique<ComponentManager<C>>();
    ComponentManager<C> &itemRef = *itemPtr;
    allManagers[type] = std::move(itemPtr);
    return itemRef;
  }

  template <typename T> void dettachComponent(Entity e) {
    ComponentManager<T> &manager = get<T>();
    manager.remove(e);
  }

  void dettachComponent(Entity e, std::type_index key) {
    if (allManagers.find(key) == allManagers.end()) {
      return;
    }
    auto &manager = *allManagers.at(key);
    manager.remove(e);
  }

  void dettachFromAllManagers(Entity e) {
    for (auto &[t, ptr] : allManagers) {
      auto &manager = *ptr;
      manager.remove(e);
    }
  };

private:
  std::unordered_map<std::type_index, std::unique_ptr<IComponentManager>>
      allManagers;
};
