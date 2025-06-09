#include "engine/components/GlobalTransformable.hpp"
#include "engine/components/RenderRectangle.hpp"
#include "engine/components/Transformable.hpp"
#include "engine/core/AbstractGame.hpp"
#include "engine/core/Engine.hpp"
#include "games/BoxSelection/core/Game.hpp"
#include "raylib.h"

#define VIRTUAL_X 360
#define VIRTUAL_Y 640

// GAME STARTING POINT ---------- //
using Entity = Entity;

int main(void) {
  Engine engine;
  Game test;
  engine.run(test);
  return 0;
}
