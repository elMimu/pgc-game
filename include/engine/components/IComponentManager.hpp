#pragma once

#include "engine/core/Types.hpp"

class IComponentManager
{
public:
  virtual ~IComponentManager() = default;
  virtual void remove(Entity e) = 0;
  virtual bool has(Entity e) = 0;
  virtual int size() = 0;
};
