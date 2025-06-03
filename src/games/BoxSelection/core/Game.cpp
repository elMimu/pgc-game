#include "games/BoxSelection/core/Game.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "games/BoxSelection/Scenes/FeedbackScene.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "games/BoxSelection/system/floatOutSystem.hpp"

void Game::load(Engine &engine) {
  /*engine.sceneManager.pushScene<GameplayScene>(engine.world);*/
  engine.sceneManager.pushScene<FeedbackScene>(engine.world);
  engine.world.setUserState<InputState>({});
  engine.world.setUserState<GameState>({});
  engine.world.componentRegistry.create<Clickable>();
  engine.world.componentRegistry.create<FloatOut>();
  engine.systemRegistry.registerSystem<ClickSystem>();
  engine.systemRegistry.registerSystem<FloatOutSystem>();
}
