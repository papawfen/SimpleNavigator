#include "ant.h"

Ant::Ant(size_t vertex) : vertex_(vertex) {
  visitedVertices_.push_back(vertex_);
}

auto Ant::GetPath() -> std::vector<int>& { return visitedVertices_; }

auto Ant::CanMove(Graph& graph) -> bool {
  possibleWays_.clear();
  for (int i = 0; i < graph.GetMatrix().size(); i++) {
    if (i != vertex_ && graph.GetMatrix()[vertex_][i] != 0 &&
        !ContainsIn(i, visitedVertices_)) {
      possibleWays_.emplace_back(i);
    }
  }
  return !possibleWays_.empty();
}

bool comp(std::pair<int, double>& p1, std::pair<int, double>& p2) {
  return p1.second < p2.second;
}

auto Ant::FindPath(Graph& graph, std::vector<std::vector<double>>& pheromons)
    -> void {
  while (CanMove(graph)) {
    double sum{0};
    std::vector<std::pair<int, double>> probabilities;
    for (auto& to : possibleWays_) {
      double pathAttraction = pow(graph.GetMatrix()[vertex_][to], alpha_);
      double amountOfPheromone = pow(pheromons[vertex_][to], beta_);
      double p = pathAttraction * amountOfPheromone;
      sum += p;
      probabilities.emplace_back(to, p);
    }
    for (auto& elem : probabilities) {
      elem.second = elem.second / sum;
    }
    double random = RandomIntInDist(100) / 100;
    std::sort(probabilities.begin(), probabilities.end(), comp);
    for (auto& elem : probabilities) {
      if (random < elem.second) {
        visitedVertices_.emplace_back(elem.first);
        vertex_ = elem.first;
        break;
      }
    }
  }
  if (graph.GetMatrix()[visitedVertices_.back()][visitedVertices_[0]] != 0 &&
      static_cast<int>(visitedVertices_.size()) == graph.GetMatrix().size()) {
    visitedVertices_.emplace_back(visitedVertices_[0]);
  } else {
    visitedVertices_.clear();
  }
}