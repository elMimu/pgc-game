#pragma once

#include "System.hpp"
#include <memory>
#include <vector>

class SystemManager
{
public:
  template <typename T> void registerSystem()
  {
    allSystems.push_back(std::make_unique<T>());
  };
  void update(float dt);

private:
  std::vector<std::unique_ptr<System>> allSystems;
};
