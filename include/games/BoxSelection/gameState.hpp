#pragma once

#include "engine/core/Types.hpp"

struct GameState {
  int rounds = 3;
  int currentRound = rounds;
  int correctChoice = 0;
  int userChoice = 0;
  float score = 0.0f;
  Entity leftBox;
  Entity rightBox;
};
