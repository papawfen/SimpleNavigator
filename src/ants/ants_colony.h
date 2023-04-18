#ifndef ANTS_COLONY_H
#define ANTS_COLONY_H

#include <cmath>

#include "../graph_algorithms.h"
#include "ant.h"


class AntsColony {
 public:
  AntsColony() = delete;
  AntsColony(Graph& graph);
  void GenerateAnts(int allAnts);
  void FindPaths();
  void UpdateFeromon();
  void UpdateResult(TsmResult& res);

 private:
  int CalculatePathCost(std::vector<int>& path);
  double pheromonRemains_ = 0.75;
  Graph& graph_;
  std::vector<std::vector<double>> pheromons_;
  std::vector<Ant> ants_;
  int allVertex_{-1};
  int averageRouteLen_;
};

#endif  // ANTS_COLONY_H