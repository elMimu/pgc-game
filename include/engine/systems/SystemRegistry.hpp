#include "engine/systems/ISystem.hpp"
#include <memory>
#include <vector>

class SystemRegistry
{
public:
  template <typename T> void registerSystem()
  {
    systems.push_back(std::move(createSystem<T>()));
  }

  void updateAllSystems(World &world, float dt)
  {
    for (auto &sys : systems)
    {
      sys->update(world, dt);
    }
  }

private:
  std::vector<std::unique_ptr<ISystem>> systems;
  template <typename T> std::unique_ptr<T> createSystem()
  {
    static_assert(std::is_base_of<ISystem, T>::value,
                  "T must be derived from ISystem");
    return std::make_unique<T>();
  }
};
