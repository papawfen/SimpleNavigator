#ifndef ANT_H
#define ANT_H

#include <algorithm>
#include <cmath>
#include <vector>

#include "../graph.h"
#include "funcs.h"

class Ant {
 public:
  Ant(size_t vertex);
  Ant() = delete;

  auto FindPath(Graph& graph, std::vector<std::vector<double>>& pheromons)
      -> void;

  std::vector<int>& GetPath();
  bool CanMove(Graph& graph);

 private:
  int vertex_{-1};
  /// alpha_ - множитель привлекательности пути, beta_ - множитель феромона
  double alpha_{2}, beta_{1};
  std::vector<int> visitedVertices_;
  std::vector<int> possibleWays_;
};

#endif  // ANT_H