#pragma once

#include "engine/core/Types.hpp"

struct GameState {
  int correctChoice = 0;
  int userChoice = 0;
  Entity leftBox;
  Entity rightBox;
};
