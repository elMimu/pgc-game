#include "games/BoxSelection/core/Game.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"

void Game::load(Engine &engine)
{
  engine.sceneManager.pushScene<GameplayScene>(engine.world);
  engine.world.setUserState<InputState>({});
  engine.world.componentRegistry.create<Clickable>();
  engine.systemRegistry.registerSystem<ClickSystem>();
}
