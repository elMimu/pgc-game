#include "games/BoxSelection/itemBoxFactory.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/components/Visual.hpp"
#include "engine/utils/TransformUtils.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "raylib.h"

Entity itemBoxFactory::createItemBox(World &world, int quantity, Vector2 origin,
                                     Vector2 position, Vector2 size,
                                     float rotation, uint32_t priority,
                                     Color boxColor, Color itemColor) {
  Entity box =
      createBox(world, origin, position, size, rotation, priority, boxColor);
  createItems(world, quantity, box, itemColor);
  return box;
}

void itemBoxFactory::createItems(World &world, int quantity, Entity parent,
                                 Color color) {
  // TODO - improve this exception handler
  /*float maxWidth = 1.0f / 4.0f;*/
  float maxWidth = 1.0f / 5.0f;
  float maxHeight = 1.0f / 5.0f;

  std::vector<Vector2> positions =
      mapItemsPosition(quantity, maxWidth, maxHeight);

  if (quantity > 10)
    quantity = 10;

  for (auto pos : positions) {
    createBoxItem(world, pos, parent, color,
                  TransformUtils::getAspect(parent, world), maxWidth,
                  maxHeight);
  }
}

Entity itemBoxFactory::createBox(World &world, Vector2 origin, Vector2 position,
                                 Vector2 size, float rotation,
                                 uint32_t priority, Color boxColor) {
  Entity box = world.entityManager.create();
  world.attach<Transformable>(box,
                              Transformable(origin, position, size, rotation));
  world.attach<Visual>(box, {boxColor, 0});
  world.attach<RenderRectangle>(box, {});
  world.attach<GlobalTransformable>(box, {});
  world.attach<ItemBoxCounter>(box, {1.0, YELLOW});
  return box;
}

Entity itemBoxFactory::createBoxItem(World &world, Vector2 position,
                                     Entity parent, Color color, float aspect,
                                     float maxWidth, float maxHeight) {
  Entity newEntity = world.entityManager.create();

  world.attach<Transformable>(
      newEntity,
      Transformable({0.5f, 0.5f}, position,
                    /*{0.95f * maxWidth, 0.95f * maxHeight}, 0.0f, parent));*/
                    {0.95f * maxWidth, 0.45f * maxHeight}, 0.0f, parent));
  world.attach<Visual>(newEntity, Visual({color, 5}));
  world.attach<GlobalTransformable>(newEntity, {});
  world.attach<RenderRectangle>(newEntity, RenderRectangle({}));

  auto &item = world.get<ItemBoxCounter>(parent);

  item.items.push(newEntity);

  return newEntity;
}

std::vector<Vector2> itemBoxFactory::mapItemsPosition(int items, float w,
                                                      float h) {
  bool isEven = (items % 2) == 0;
  if (isEven) {
    return mapEvenItemsPosition(items, w, h);
  }
  return mapOddItemsPosition(items, w, h);
};

std::vector<Vector2> itemBoxFactory::mapEvenItemsPosition(int items, float w,
                                                          float h) {
  switch (items) {
  case 2:
    return {
        {0.5f - w / 2.0f, 0.5f},
        {0.5f + w / 2.0f, 0.5f},
    };
  case 4:
    return {
        {0.5f - w / 2.0f, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f, 0.5f + h / 2.0f},
        {0.5f + w / 2.0f, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f, 0.5f + h / 2.0f},
    };
  case 6:
    return {
        {0.5f - w / 2.0f, 0.5f - h}, {0.5f - w / 2.0f, 0.5f + h},
        {0.5f - w / 2.0f, 0.5f},     {0.5f + w / 2.0f, 0.5f},
        {0.5f + w / 2.0f, 0.5f - h}, {0.5f + w / 2.0f, 0.5f + h},
    };
  case 8:
    return {
        {0.5f - w / 2.0f, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f - w, 0.5f - h / 2.0f},
        {0.5f - w / 2.0f, 0.5f + h / 2.0f},
        {0.5f - w / 2.0f - w, 0.5f + h / 2.0f},

        {0.5f + w / 2.0f, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f + w, 0.5f - h / 2.0f},
        {0.5f + w / 2.0f, 0.5f + h / 2.0f},
        {0.5f + w / 2.0f + w, 0.5f + h / 2.0f},
    };
  default:
    return {
        {0.5f - w / 2.0f, 0.5f - 2 * h}, {0.5f - w / 2.0f, 0.5f - h},
        {0.5f - w / 2.0f, 0.5f},         {0.5f - w / 2.0f, 0.5f + h},
        {0.5f - w / 2.0f, 0.5f + 2 * h},

        {0.5f + w / 2.0f, 0.5f - 2 * h}, {0.5f + w / 2.0f, 0.5f - h},
        {0.5f + w / 2.0f, 0.5f},         {0.5f + w / 2.0f, 0.5f + h},
        {0.5f + w / 2.0f, 0.5f + 2 * h},
    };
  }
};

std::vector<Vector2> itemBoxFactory::mapOddItemsPosition(int items, float w,
                                                         float h) {
  switch (items) {
  case 1:
    return {{0.5f, 0.5f}};
  case 3:
    return {{0.5f - w, 0.5f}, {0.5, 0.5}, {0.5f + w, 0.5f}};
  case 5:
    return {{0.5f - w, 0.5f - h},
            {0.5f - w, 0.5f + h},
            {0.5f, 0.5f},
            {0.5f + w, 0.5f - h},
            {0.5f + w, 0.5f + h}};
  case 7:
    return {{0.5f - w, 0.5f - h}, {0.5f - w, 0.5f + h}, {0.5f, 0.5f - h},
            {0.5f, 0.5f},         {0.5f, 0.5f + h},     {0.5f + w, 0.5f - h},
            {0.5f + w, 0.5f + h}};
  default:
    return {{0.5f - w, 0.5f - h}, {0.5f - w, 0.5f + h}, {0.5f, 0.5f - h},
            {0.5f - w, 0.5f},     {0.5f, 0.5f},         {0.5f + w, 0.5f},
            {0.5f, 0.5f + h},     {0.5f + w, 0.5f - h}, {0.5f + w, 0.5f + h}};
  };
};
