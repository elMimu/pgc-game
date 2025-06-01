#include "engine/core/Types.hpp"
#include "games/BoxSelection/itemBoxFactory.hpp"

class ClickableBoxFactory
{
public:
  Entity creatClickableBox(World &world, int quantity, Vector2 origin,
                           Vector2 position, Vector2 size, float rotation,
                           uint32_t priority, Color boxColor, Color itemColor)
  {
    Entity box =
        itemBoxFactory::createItemBox(world, quantity, origin, position, size,
                                      rotation, priority, boxColor, itemColor);
    return box;
  }

private:
};
