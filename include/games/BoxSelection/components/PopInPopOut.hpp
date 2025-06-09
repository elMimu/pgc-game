
#pragma once

#include "raylib.h"
struct PopInPopOut {
  enum ACTION { POPIN, POPOUT, IDLE };
  Vector2 popInScale;
  ACTION action = IDLE;
  Vector2 popOutScale = {0.0f, 0.0f};
};
