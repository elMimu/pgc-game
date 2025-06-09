#include "games/BoxSelection/core/Game.hpp"
#include "engine/systems/ClickSystem.hpp"
#include "games/BoxSelection/Scenes/GameplayScene.hpp"
#include "games/BoxSelection/components/FloatOut.hpp"
#include "games/BoxSelection/components/PopInPopOut.hpp"
#include "games/BoxSelection/components/ScaleAnimation.hpp"
#include "games/BoxSelection/components/ScaleLerp.hpp"
#include "games/BoxSelection/components/itemBoxCounter.hpp"
#include "games/BoxSelection/gameState.hpp"
#include "games/BoxSelection/system/PopInPopOutSystem.hpp"
#include "games/BoxSelection/system/ScaleLerpSystem.hpp"
#include "games/BoxSelection/system/floatOutSystem.hpp"
#include "games/BoxSelection/system/itemBoxCounterSystem.hpp"
#include "games/BoxSelection/system/scaleAnimationSystem.hpp"

void Game::load(Engine &engine) {
  engine.sceneManager.pushScene<GameplayScene>(engine.world);
  engine.world.setUserState<InputState>({});
  engine.world.setUserState<GameState>({});
  engine.world.componentRegistry.create<Clickable>();
  engine.world.componentRegistry.create<FloatOut>();
  engine.world.componentRegistry.create<ItemBoxCounter>();
  engine.world.componentRegistry.create<ScaleLerp>();
  engine.world.componentRegistry.create<ScaleAnimation>();
  engine.world.componentRegistry.create<PopInPopOut>();
  engine.systemRegistry.registerSystem<ClickSystem>();
  engine.systemRegistry.registerSystem<FloatOutSystem>();
  engine.systemRegistry.registerSystem<itemBoxCounterSystem>();
  engine.systemRegistry.registerSystem<ScaleLerpSystem>();
  engine.systemRegistry.registerSystem<ScaleAnimationSystem>();
  engine.systemRegistry.registerSystem<PopInPopOutSystem>();
}
