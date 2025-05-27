#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/AbstractGame.hpp"
#include "engine/core/Engine.hpp"
#include "raylib.h"

#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// GAME ---------- //
class MyGame : public AbstractGame
{
public:
  float time = 0;
  MyGame() : AbstractGame(VIRTUAL_X, VIRTUAL_Y) {}
  void load(Engine &engine) override
  {
    // Create simple entities
    Entity redSquare = engine.world.entityManager.create();
    Entity blueSquare = engine.world.entityManager.create();

    // attach components to entities
    // Transformable
    std::cout << "abc " << getVirtualY() << "\n";
    engine.world.attach<Transformable>(
        redSquare, Transformable({0.5f, 0.5f},
                                 {0.75f * getVirtualX(), 0.75f * getVirtualY()},
                                 {
                                     0.25f * getVirtualX(),
                                     0.25f * getVirtualX(),
                                 },
                                 30 * DEG2RAD));

    engine.world.attach<Transformable>(blueSquare,
                                       Transformable({0.5f, 0.5f}, {1.0f, 1.0f},
                                                     {
                                                         0.5f,
                                                         0.5f,
                                                     },
                                                     0.0f, redSquare));

    engine.world.attach<GlobalTransformable>(blueSquare, {});
    engine.world.attach<GlobalTransformable>(redSquare, {});

    // RectRender
    // FIX -- inverted order of parenting
    engine.world.attach<RenderRectangle>(blueSquare, {0, BLUE});
    engine.world.attach<RenderRectangle>(redSquare, {0, RED});
  }

  void update(float dt) override {}
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
