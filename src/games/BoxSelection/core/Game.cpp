#include "games/BoxSelection/core/Game.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "games/BoxSelection/gameState.hpp"

void Game::load(Engine &engine) {
  engine.sceneManager.pushScene<GameplayScene>(engine.world);
  engine.world.setUserState<InputState>({});
  engine.world.setUserState<GameState>({});
  engine.world.componentRegistry.create<Clickable>();
  engine.systemRegistry.registerSystem<ClickSystem>();
}
