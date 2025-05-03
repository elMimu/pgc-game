#include "engine/components/ComponentManager.hpp"
#include "engine/components/TransformComponent.hpp"
#include "engine/core/AbstractGame.hpp"
#include "engine/core/Engine.hpp"
#include "engine/entity/EntityManager.hpp"

#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// GAME ---------- //
class MyGame : public AbstractGame
{
public:
  MyGame() : AbstractGame(VIRTUAL_X, VIRTUAL_Y) {}
  void load(Engine &engine) override
  {
    // PLACE GAME CODE HERE
    Entity a = engine.entityManager.create();
    Entity b = engine.entityManager.create();
    Entity c = engine.entityManager.create();

    // CREATE REGISTER

    engine.componentRegistry.registerManager<TransformComponent>();
    ComponentManager<TransformComponent> &transformManager =
        engine.componentRegistry.getManager<TransformComponent>();

    transformManager.add(a, {{0.0f, 0.0f},
                             {VIRTUAL_X / 2.0f, VIRTUAL_Y / 2.0f},
                             {20.0f, 20.0f},
                             0});
    transformManager.add(b, {{0.0f, 0.0f},
                             {VIRTUAL_X * 0.75f, VIRTUAL_Y * 0.5f},
                             {20.0f, 20.0f},
                             0});
    transformManager.add(c, {{0.0f, 0.0f},
                             {VIRTUAL_X * 0.25f, VIRTUAL_Y * 0.5f},
                             {20.0f, 20.0f},
                             0});

    transformManager.printAttachedEntities();
  }

  void update(float dt) override
  {
    // PLACE UPDATE SCENE FUNCTIONS HERE
    // TODO - MAYBE AVOID THIS SOMEHOW
  }
};

// GAME STARTING POINT ---------- //
using Entity = Entity;

int main(void)
{
  Engine engine;
  MyGame test;
  engine.run(test);
  return 0;
}
