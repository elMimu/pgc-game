#include "engine/systems/SystemManager.hpp"

void SystemManager::update(float dt)
{
  for (auto &system : allSystems)
  {
    system->update(dt);
  }
}
