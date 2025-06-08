#pragma once

#include "engine/components/ComponentRegistry.hpp"
#include "engine/components/View.hpp"
#include "engine/core/CommandBuffer.hpp"
#include "engine/core/Types.hpp"
#include "engine/entity/EntityManager.hpp"
#include "engine/state/UserState.hpp"
#include "engine/utils/FontLoader.hpp"
#include "raylib.h"
#include <tuple>

class World {
public:
  EntityManager entityManager;
  ComponentRegistry componentRegistry;
  CommandBuffer commandBuffer;
  FontLoader fontLoader;

  Vector2 getScreenCoord() {
    return Vector2{GetScreenWidth() * 1.0f, GetScreenHeight() * 1.0f};
  };

  void flush() { commandBuffer.flush(entityManager, componentRegistry); }

  void destroy(Entity e) { commandBuffer.destroy(e); }

  void dettachFromAll(Entity e) { commandBuffer.dettachAll(e); }

  template <typename T> void dettach(Entity e) {
    std::type_index type = std::type_index(typeid(T));
    commandBuffer.dettach(e, type);
  }

  template <typename T> bool has(Entity e) {
    return componentRegistry.get<T>().has(e);
  }

  template <typename T> T &attach(Entity e, const T &component) {
    return componentRegistry.get<T>().attach(e, component);
  }

  template <typename T> T &get(Entity e) {
    return componentRegistry.get<T>().getComponent(e);
  }

  template <typename... Ts> View<Ts...> view() {
    return View<Ts...>(std::tie(componentRegistry.get<Ts>()...));
  };

  template <typename T> void setUserState(T state) {
    userState[typeid(T)] =
        std::make_unique<UserStateHolder<T>>(std::move(state));
  }

  template <typename T> T &getUserState() {
    auto it = userState.find(typeid(T));
    if (it == userState.end()) {
      throw std::runtime_error("User state for this type does not exist");
    }

    auto *holder = static_cast<UserStateHolder<T> *>(it->second.get());
    return holder->data;
  }

private:
  std::unordered_map<std::type_index, std::unique_ptr<UserStateBase>> userState;
};
