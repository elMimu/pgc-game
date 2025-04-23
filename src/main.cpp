#include "list"
#include "raylib.h"
#include "raymath.h"

// DEFINING VIRTUAL RESOLUTION --------- //
#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// GAME STARTING POINT ---------- //
int main(void)
{

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(VIRTUAL_X, VIRTUAL_Y, "First Minigame");

  SetTargetFPS(60);

  bool once = true;
  while (!WindowShouldClose())
  {
    float time = GetTime();

    BeginDrawing();
    ClearBackground(DARKGRAY);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
