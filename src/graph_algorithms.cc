#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int startVertex) {
  if (startVertex < 1 || startVertex > graph.GetMatrix().size())
    throw std::invalid_argument("wrong start vertex");
  startVertex -= 1;
  count = graph.GetMatrix().size();
  path = std::vector<int>(count);
  visited_vertex = std::vector<bool>(count);
  std::stack<int> vert_stack[count];

  path[0] = startVertex + 1;
  visited_vertex[startVertex] = true;
  vert_stack->push(startVertex);
  int r = 1;
  while (!vert_stack->empty()) {
    int v = vert_stack->top();
    vert_stack->pop();
    for (int i = 0; i < count; ++i) {
      if (graph.GetMatrix()[v][i] != 0 && !visited_vertex[i]) {
        vert_stack->push(i);
        visited_vertex[i] = true;
        path[r] = i + 1;
        ++r;
        break;
      }
    }
  }
  bool isolated = true;
  for (int i = 0; i < count; ++i) {
    if (!visited_vertex[i]) {
      for (int j = 0; j < graph.GetMatrix().size(); ++j) {
        if (graph.GetMatrix()[j][i] != 0 && !visited_vertex[j]) {
          path[r] = i + 1;
          isolated = false;
          ++r;
        }
        if (!isolated) {
          isolated = true;
          --count;
        }
      }
    }
  }
  return path;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int startVertex) {
  if (startVertex < 0 || startVertex > graph.GetMatrix().size())
    throw std::invalid_argument("wrong start vertex");
  count = graph.GetMatrix().size();
  startVertex -= 1;
  path = std::vector<int>(count);
  visited_vertex = std::vector<bool>(count);
  std::queue<int> queue;
  visited_vertex.at(startVertex) = true;
  queue.push(startVertex);
  path.at(0) = startVertex + 1;
  int r = 1;
  while (!queue.empty()) {
    int current = queue.front();
    queue.pop();
    for (int i = 0; i < count; ++i) {
      if (graph.GetMatrix()[current][i] > 0 && !visited_vertex.at(i)) {
        path.at(r) = i + 1;
        visited_vertex.at(i) = true;
        queue.push(i);
        ++r;
      }
    }
  }
  return path;
}

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                                    int vertex2) {
  count = graph.GetMatrix().size();
  vertex1 -= 1;
  vertex2 -= 1;
  path = std::vector<int>(count + 1);
  visited_vertex = std::vector<bool>(count);
  weights = std::vector<int>(count, INT_MAX);
  std::queue<int> neighbors;
  weights.at(vertex1) = 0;
  path.at(0) = vertex1;
  visited_vertex.at(vertex1) = true;
  neighbors.push(vertex1);
  int v = 1;

  while (!neighbors.empty()) {
    int current = neighbors.front();
    int next = -1, min = INT_MAX;
    neighbors.pop();
    for (int i = 0; i < count; ++i) {
      if (weights.at(i) > graph.GetMatrix()[current][i] + weights.at(current) &&
          !visited_vertex.at(i) && graph.GetMatrix()[current][i] != 0) {
        weights.at(i) = graph.GetMatrix()[current][i] + weights.at(current);
        if (min > weights.at(i)) {
          min = weights.at(i);
          next = i;
        }
      } else if (weights.at(i) <
                     graph.GetMatrix()[current][i] + weights.at(current) &&
                 graph.GetMatrix()[current][i] != 0 && !visited_vertex.at(i)) {
        min = weights.at(i);
        next = i;
      }
    }
    if (next != -1) {
      neighbors.push(next);
      path.at(v) = next;
      visited_vertex.at(next) = true;
      ++v;
    }
  }
  return weights.at(vertex2);
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph &graph) {
  count = graph.GetMatrix().size();
  std::vector<std::vector<int>> result(count, std::vector<int>(count));
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < count; ++j) {
      if (i == j) {
        result[i][j] = 0;
      } else if (i != j && graph.GetMatrix()[i][j] > 0) {
        result[i][j] = graph.GetMatrix()[i][j];
      } else if (i != j && graph.GetMatrix()[i][j] == 0) {
        result[i][j] = INT_MAX;
      }
    }
  }
  for (int k = 0; k < count; ++k) {
    for (int i = 0; i < count; ++i) {
      for (int j = 0; j < count; ++j) {
        if (result[i][k] < INT_MAX && result[k][j] < INT_MAX)
          result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);
      }
    }
  }
  return result;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    Graph &graph) {
  count = graph.GetMatrix().size();
  visited_vertex = std::vector<bool>(count);
  path = std::vector<int>(count, -1);
  std::vector<int> min(count, INT_MAX);
  min[0] = 0;
  std::vector<std::vector<double>> tmp = graph.GetMatrix();
  std::vector<std::vector<int>> res(count, std::vector<int>(count));
  for (int i = 0; i < count; ++i) {
    for (int j = 0; j < count; ++j) {
      if (i != j && tmp[i][j] == 0) {
        tmp[i][j] = INT_MAX;
      }
    }
  }
  for (int i = 0; i < count; ++i) {
    int vert = -1;
    for (int j = 0; j < count; ++j) {
      if (!visited_vertex.at(j) && (vert == -1 || min[j] < min[vert])) {
        vert = j;
      }
    }
    if (min[vert] == INT_MAX) {
      std::cout << "wrong graph";
      exit(0);
    }
    visited_vertex.at(vert) = true;
    if (path.at(vert) != -1) {
      res[path.at(vert)][vert] = tmp[path.at(vert)][vert];
      res[vert][path.at(vert)] = tmp[vert][path.at(vert)];
    }
    for (int k = 0; k < count; ++k) {
      if (tmp[vert][k] < min[k]) {
        min[k] = tmp[vert][k];
        path.at(k) = vert;
      }
    }
  }
  return res;
}
