#include "engine/core/Engine.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/IGame.hpp"
#include "engine/render/RenderRectSystem.hpp"
#include "engine/systems/GlobalTransformSystem.hpp"
#include "raylib.h"
#include "rlgl.h"

void Engine::loadDefaults()
{
  createDefaultComponentManagers();
  createDefaultSystems();
  registerDefaultRenderSystems();
}

void Engine::createDefaultComponentManagers()
{
  world.componentRegistry.create<Transformable>();
  world.componentRegistry.create<GlobalTransformable>();
  world.componentRegistry.create<RenderRectangle>();
}

void Engine::createDefaultSystems()
{
  systemRegistry.registerSystem<GlobalTransformSystem>();
}

void Engine::registerDefaultRenderSystems()
{
  renderSystemRegistry.registerSystem(RenderRectSystem());
}

void Engine::run(IGame &game)
{
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(game.getVirtualX(), game.getVirtualY(), "MULTI MINIGAME SYSTEM");

  SetTargetFPS(60);

  game.load(*this);

  while (!WindowShouldClose())
  {
    float time = GetTime();
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(DARKGRAY);

    systemRegistry.updateAllSystems(world, dt);
    sceneManager.update(world, dt);
    renderSystemRegistry.registerAllComponentsJobs(renderJobRegistry, world);
    renderJobRegistry.flush();

    EndDrawing();
  }
}
