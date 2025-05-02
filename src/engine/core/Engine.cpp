#include "engine/core/Engine.hpp"
#include "engine/core/IGame.hpp"
#include "raylib.h"

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

    game.update(dt);

    EndDrawing();
  }
}
