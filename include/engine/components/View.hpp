#pragma once
#include "engine/components/ComponentManager.hpp"
#include "engine/components/ViewIterator.hpp"
#include <tuple>

template <typename... Ts> class View
{
public:
  View(std::tuple<ComponentManager<Ts> &...> componentManagers)
      : componentManagers(componentManagers)
  {
  }

  auto begin()
  {
    using Anchor = std::tuple_element_t<0, std::tuple<Ts...>>;
    auto &anchorManager =
        std::get<ComponentManager<Anchor> &>(componentManagers);

    return ViewIterator<Ts...>(anchorManager.getAll().begin(),
                               anchorManager.getAll().end(), componentManagers);
  }

  auto end()
  {
    using Anchor = std::tuple_element_t<0, std::tuple<Ts...>>;
    auto &anchorManager =
        std::get<ComponentManager<Anchor> &>(componentManagers);

    return ViewIterator<Ts...>(anchorManager.getAll().end(),
                               anchorManager.getAll().end(), componentManagers);
  }

private:
  std::tuple<ComponentManager<Ts> &...> componentManagers;
};
