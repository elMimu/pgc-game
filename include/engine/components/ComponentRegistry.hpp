#pragma once

#include "engine/components/ComponentManager.hpp"
#include "engine/components/IComponentManager.hpp"
#include <memory>
#include <typeindex>
#include <unordered_map>

class ComponentRegistry
{
public:
  using ManagerMap =
      std::unordered_map<std::type_index, std::unique_ptr<IComponentManager>>;

  bool hasManager(std::type_index type)
  {
    return allManagers.find(type) != allManagers.end();
  }

  template <typename T> void registerManager()
  {
    std::type_index type = std::type_index(typeid(T));

    if (hasManager(type))
    {
      return;
    }

    allManagers.insert({type, std::make_unique<ComponentManager<T>>()});
  }

  template <typename T> void registerEntity(Entity e, const T &component)
  {
    ComponentManager<T> &manager = getManager<T>();
    manager.add(e, component);
  }

  template <typename T> ComponentManager<T> &getManager()
  {

    std::type_index type = std::type_index(typeid(T));

    if (!hasManager(type))
    {
      // TODO - HANDLE DOESN'T EXIST EXCEPTION
      registerManager<T>();
    }

    return *static_cast<ComponentManager<T> *>(allManagers.at(type).get());
  }

  void removeAllManagers(Entity e)
  {
    for (auto &[t, pt] : allManagers)
    {
      pt->remove(e);
    }
  }

private:
  ManagerMap allManagers;
};
