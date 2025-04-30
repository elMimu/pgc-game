#pragma once

class System
{
public:
    ~System() = default;
  virtual void update(float dt) = 0;
};
