#include "funcs.h"

bool ContainsIn(int vertex, std::vector<int>& vertices) {
  for (int elem : vertices) {
    if (elem == vertex) return true;
  }
  return false;
}

int RandomIntInDist(size_t dist) {
  std::random_device rd;
  std::default_random_engine engine{rd()};
  std::uniform_int_distribution<int> distribution{0,
                                                  static_cast<int>(dist) - 1};
  return distribution(engine);
}
