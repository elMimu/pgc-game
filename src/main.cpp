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
    EntityManager::Entity a = engine.entityManager.create();
    EntityManager::Entity b = engine.entityManager.create();
    EntityManager::Entity c = engine.entityManager.create();

    engine.entityManager.print();
  }

  void update(float dt) override
  {
    // PLACE UPDATE SCENE FUNCTIONS HERE
    // TODO - MAYBE AVOID THIS SOMEHOW
  }
};

// GAME STARTING POINT ---------- //
using Entity = EntityManager::Entity;

int main(void)
{
  Engine engine;
  MyGame test;
  engine.run(test);
  return 0;
}
