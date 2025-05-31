#pragma once

#include "engine/core/World.hpp"
#include "engine/render/RenderJobRegistry.hpp"
#include "engine/render/RenderSystemRegistry.hpp"
#include "engine/scene/SceneManager.hpp"
#include "engine/systems/SystemRegistry.hpp"

// FORWARD DECLARATION
class IGame;

class Engine
{
public:
  World world;
  RenderJobRegistry renderJobRegistry;
  RenderSystemRegistry renderSystemRegistry;
  SystemRegistry systemRegistry;
  SceneManager sceneManager;

  Engine() { loadDefaults(); }
  void loadDefaults();
  void loadDefaultFonts();
  void createDefaultComponentManagers();
  void createDefaultSystems();
  void registerDefaultRenderSystems();

  void run(IGame &game);
};
