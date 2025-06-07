#pragma once

#include "engine/systems/System.hpp"
#include "games/BoxSelection/components/PopInPopOut.hpp"
#include "games/BoxSelection/components/ScaleAnimation.hpp"

class PopInPopOutSystem : public System<PopInPopOut, ScaleAnimation> {
  void updateEntity(World &world, Entity e, float dt, PopInPopOut &ppio,
                    ScaleAnimation &sca) override {
    if (ppio.action == PopInPopOut::ACTION::IDLE) {
      return;
    }

    if (ppio.action == PopInPopOut::ACTION::POPIN) {
      std::cout << "azn\n";
      sca.startScale = ppio.popOutScale;
      sca.endScale = ppio.popInScale;
      sca.play = true;
      sca.progress = 0.0f;
      ppio.action = PopInPopOut::ACTION::IDLE;
    }

    if (ppio.action == PopInPopOut::ACTION::POPOUT) {
      sca.startScale = ppio.popInScale;
      sca.endScale = ppio.popOutScale;
      sca.play = true;
      sca.progress = 0.0f;
      ppio.action = PopInPopOut::ACTION::IDLE;
    }
  }
};
