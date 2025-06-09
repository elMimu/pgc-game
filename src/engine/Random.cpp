#include "engine/utils/Random.hpp"
#include <random>

int getRandomInt(int a, int b) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> dist(a, b);
  return dist(rng);
}
