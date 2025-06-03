#include "engine/core/Engine.hpp"
#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/IGame.hpp"
#include "engine/render/RenderRectSystem.hpp"
#include "engine/render/RenderTextSystem.hpp"
#include "engine/systems/GlobalTransformSystem.hpp"
#include "raylib.h"
#include "rlgl.h"

void Engine::loadDefaults() {
  createDefaultComponentManagers();
  createDefaultSystems();
  registerDefaultRenderSystems();
}

void Engine::createDefaultComponentManagers() {
  world.componentRegistry.create<Transformable>();
  world.componentRegistry.create<GlobalTransformable>();
  world.componentRegistry.create<Visual>();
  world.componentRegistry.create<RenderRectangle>();
  world.componentRegistry.create<RenderText>();
}

void Engine::createDefaultSystems() {
  systemRegistry.registerSystem<GlobalTransformSystem>();
}

void Engine::loadDefaultFonts() {
  world.fontLoader.loadFontEx("chewy",
                              RESOURCES_PATH "fonts/Chewy-Regular.ttf");
}

void Engine::registerDefaultRenderSystems() {
  renderSystemRegistry.registerRender<RenderRectSystem>();
  renderSystemRegistry.registerRender<RenderTextSystem>();
}

void Engine::run(IGame &game) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(game.getVirtualX(), game.getVirtualY(), "MULTI MINIGAME SYSTEM");

  loadDefaultFonts();

  SetTargetFPS(60);

  game.load(*this);

  while (!WindowShouldClose()) {
    float time = GetTime();
    float dt = GetFrameTime();

    BeginDrawing();
    ClearBackground(DARKGRAY);

    systemRegistry.updateAllSystems(world, dt);
    sceneManager.update(world, dt);
    renderSystemRegistry.registerAllComponentsJobs(renderJobRegistry, world);
    renderJobRegistry.flush();
    world.flush();

    EndDrawing();
  }
}
