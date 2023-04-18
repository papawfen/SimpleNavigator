#include "ants/ants_colony.h"
#include "graph_algorithms.h"


TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph& graph) {
  int antsNumber = graph.GetMatrix().size();
  int CountWithoutUpgrade = 30, maxCount = 50;

  AntsColony colony(graph);
  TsmResult prevRes, res;
  prevRes.distance = INFINITY;
  res.distance = INFINITY;

  while (CountWithoutUpgrade) {
    colony.GenerateAnts(antsNumber);
    colony.FindPaths();
    colony.UpdateFeromon();
    colony.UpdateResult(res);

    if (res.distance == prevRes.distance) {
      CountWithoutUpgrade--;
    } else {
      prevRes = res;
      CountWithoutUpgrade = maxCount;
    }
  }
  return res;
}
