#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/components/View.hpp"
#include "engine/core/Types.hpp"
#include "engine/entity/EntityManager.hpp"
#include "engine/state/UserState.hpp"
#include "engine/utils/FontLoader.hpp"
#include <tuple>

class World
{
public:
  EntityManager entityManager;
  ComponentRegistry componentRegistry;
  FontLoader fontLoader;

  void destroyEntity(Entity e)
  {
    componentRegistry.dettachFromAllManagers(e);
    entityManager.destroy(e);
  }

  template <typename T> void attach(Entity e, const T &component)
  {
    componentRegistry.get<T>().attach(e, component);
  }

  template <typename T> T &get(Entity e)
  {
    return componentRegistry.get<T>().getComponent(e);
  }

  template <typename... Ts> View<Ts...> view()
  {
    return View<Ts...>(std::tie(componentRegistry.get<Ts>()...));
  };

  template <typename T> void setUserState(T state)
  {
    userState[typeid(T)] =
        std::make_unique<UserStateHolder<T>>(std::move(state));
  }

  template <typename T> T &getUserState()
  {
    auto it = userState.find(typeid(T));
    if (it == userState.end())
    {
      throw std::runtime_error("User state for this type does not exist");
    }

    auto *holder = static_cast<UserStateHolder<T> *>(it->second.get());
    return holder->data;
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<UserStateBase>> userState;
};
