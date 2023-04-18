#ifndef GRAPH_ALGORITHMS_H
#define GRAPH_ALGORITHMS_H

#include <climits>
#include <limits>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "graph.h"


struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int startVertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int startVertex);
  int GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2);
  std::vector<std::vector<int> > GetShortestPathsBetweenAllVertices(
      Graph &graph);
  std::vector<std::vector<int> > GetLeastSpanningTree(Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  std::vector<int> path;
  std::vector<bool> visited_vertex;
  std::vector<int> weights;
  int count;
};

#endif  // GRAPH_ALGORITHMS_H
