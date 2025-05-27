#pragma once

#include "engine/components/ComponentManager.hpp"
#include "engine/core/Types.hpp"
#include <tuple>
#include <unordered_map>

template <typename... Ts> class ViewIterator
{
private:
  using Anchor = std::tuple_element_t<0, std::tuple<Ts...>>;
  using AnchorIter = typename std::unordered_map<Entity, Anchor>::iterator;

public:
  ViewIterator(AnchorIter current, AnchorIter end,
               std::tuple<ComponentManager<Ts> &...> componentManagers)
      : current(current), end(end), componentManagers(componentManagers)
  {
    advanceToNextValid();
  }

  bool operator!=(const ViewIterator &other) const
  {
    return current != other.current;
  }

  ViewIterator &operator++()
  {
    ++current;
    advanceToNextValid();
    return *this;
  }

  auto operator*()
  {
    return std::tuple_cat(std::tie(current->first),
                          getAllComponents(current->first));
  }

private:
  AnchorIter current;
  AnchorIter end;
  std::tuple<ComponentManager<Ts> &...> componentManagers;

  void advanceToNextValid()
  {
    while (current != end && !hasAllComponents(current->first))
    {
      ++current;
    }
  }

  auto getAllComponents(Entity e) const
  {
    return std::tie(getComponent<Ts>(e)...);
  }

  template <typename C> C &getComponent(Entity e) const
  {
    return std::get<ComponentManager<C> &>(componentManagers).getComponent(e);
  }

  template <typename C> bool hasComponent(Entity e) const
  {
    return std::get<ComponentManager<C> &>(componentManagers).has(e);
  }

  bool hasAllComponents(Entity e) const { return (hasComponent<Ts>(e) && ...); }
};
