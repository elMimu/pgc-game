#include "games/BoxSelection/core/Game.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "games/BoxSelection/system/floatOutSystem.hpp"
#include "games/BoxSelection/system/itemBoxCounterSystem.hpp"

void Game::load(Engine &engine) {
  engine.sceneManager.pushScene<GameplayScene>(engine.world);
  engine.world.setUserState<InputState>({});
  engine.world.setUserState<GameState>({});
  engine.world.componentRegistry.create<Clickable>();
  engine.world.componentRegistry.create<FloatOut>();
  engine.world.componentRegistry.create<ItemBoxCounter>();
  engine.systemRegistry.registerSystem<ClickSystem>();
  engine.systemRegistry.registerSystem<FloatOutSystem>();
  engine.systemRegistry.registerSystem<itemBoxCounterSystem>();
}
