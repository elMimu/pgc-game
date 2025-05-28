#include "games/BoxSelection/core/Game.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"

#define VIRTUAL_X 360
#define VIRTUAL_Y 640

void Game::load(Engine &engine)
{
  engine.sceneManager.pushScene<GameplayScene>(engine.world);
}
