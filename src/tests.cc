#include <gtest/gtest.h>

#include "graph.h"
#include "graph_algorithms.h"

TEST(DepthFirstSearch, DFS) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  std::vector<int> res = algo.DepthFirstSearch(graph, 1);
  std::vector<int> orig = {1, 2, 3, 4, 5, 6};
  ASSERT_TRUE(res == orig);
}

TEST(BreadthFirstSearch, BFS) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  std::vector<int> res = algo.BreadthFirstSearch(graph, 1);
  std::vector<int> orig = {1, 2, 3, 6, 4, 5};
  ASSERT_TRUE(res == orig);
}

TEST(ShortestPathBetweenVertices, DIJKSTRA) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  int res = algo.GetShortestPathBetweenVertices(graph, 1, 5);
  int orig = 20;
  ASSERT_TRUE(res == orig);
}

TEST(ShortestPathsBetweenAllVertices, FLOYD_WARSHALL) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  std::vector<std::vector<int>> res =
      algo.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> orig = {
      {0, 7, 9, 20, 20, 11},  {7, 0, 10, 15, 21, 12}, {9, 10, 0, 11, 11, 2},
      {20, 15, 11, 0, 6, 13}, {20, 21, 11, 6, 0, 9},  {11, 12, 2, 13, 9, 0}};
  ASSERT_TRUE(res == orig);
}

TEST(GetLeastSpanningTree, PRIM) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  std::vector<std::vector<int>> res = algo.GetLeastSpanningTree(graph);
  std::vector<std::vector<int>> orig = {{0, 7, 9, 0, 0, 0}, {7, 0, 0, 0, 0, 0},
                                        {9, 0, 0, 0, 0, 2}, {0, 0, 0, 0, 6, 0},
                                        {0, 0, 0, 6, 0, 9}, {0, 0, 2, 0, 9, 0}};
  ASSERT_TRUE(res == orig);
}

TEST(SolveTravelingSalesmanProblem, ANTS) {
  Graph graph;
  GraphAlgorithms algo;
  graph.LoadGraphFromFile("graph_test.txt");
  TsmResult res = algo.SolveTravelingSalesmanProblem(graph);
  double orig_dist = 48;
  ASSERT_TRUE(res.distance == orig_dist);
}