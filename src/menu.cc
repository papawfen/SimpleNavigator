#include "menu.h"

#include <iostream>
#include <string>

int main() {
  Menu menu;
  menu.MainMenu();
  return 0;
}

void Menu::MainMenu() {
  while (choose != "q" || choose != "Q") {
    std::system("clear");
    std::cout << "1. Load graph from file" << std::endl
              << "2. DFS algorithm" << std::endl
              << "3. BFS algorithm" << std::endl
              << "4. Shortest Path Between Vertices (Dijkstra)" << std::endl
              << "5. Shortest Paths Between All Vertices (Floyd-Warshall)"
              << std::endl
              << "6. Least Spanning Tree (Prim)" << std::endl
              << "7. Traveling Salesman Problem" << std::endl;
    std::cin >> choose;
    SelectMethodToPrint();
  }
}

void Menu::SelectMethodToPrint() {
  std::string back;
  while (back != "back") {
    if (choose == "1") {
      loaded = false;
      while (!loaded) {
        std::cout << "write path to file" << std::endl;
        std::string path;
        std::cin >> path;
        try {
          graph.LoadGraphFromFile(path);
          loaded = true;
          std::cout << "Success" << std::endl;
        } catch (...) {
          std::cout << "wrong path or input file, try again" << std::endl;
          fflush(stdin);
        }
      }
    } else if ((choose == "2" || choose == "3") && loaded) {
      std::string start;
      while (true) {
        try {
          std::cout << "Write start vertex" << std::endl;
          std::cin >> start;
          std::vector<int> res;
          if (choose == "2") {
            res = algorithms.DepthFirstSearch(graph, stod(start));
          } else {
            res = algorithms.BreadthFirstSearch(graph, stod(start));
          }
          for (auto i : res) {
            std::cout << i << "->";
          }
          break;
        } catch (...) {
          std::cout << "Vertex is out of range, try again" << std::endl;
          fflush(stdin);
        }
      }
      std::cout << std::endl;
    } else if (choose == "4" && loaded) {
      std::string start, end;
      while (true) {
        try {
          std::cout << "Write start vertex and end vertex" << std::endl;
          std::cin >> start >> end;
          int res =
              algorithms.GetShortestPathBetweenVertices(graph, stod(start), stod(end));
          std::cout << "Weight of shortest path: " << res << std::endl;
          break;
        } catch (...) {
          std::cout << "Vertex is out of range, try again" << std::endl;
          fflush(stdin);
        }
      }
    } else if ((choose == "5" || choose == "6") && loaded) {
      std::vector<std::vector<int> > res;
      if (choose == "5") {
        res = algorithms.GetShortestPathsBetweenAllVertices(graph);
      } else {
        res = algorithms.GetLeastSpanningTree(graph);
      }
      for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res.size(); ++j) {
          std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
      }
    } else if (choose == "7") {
      TsmResult result;
      result = algorithms.SolveTravelingSalesmanProblem(graph);
      for (auto i : result.vertices) std::cout << i << "->";
      std::cout << std::endl << result.distance << std::endl;
    } else if (!loaded) {
      std::cout << "Please load graph" << std::endl;
    }
    choose = "0";
    std::cout << "Type back to return to main menu" << std::endl;
    std::cin >> back;
  }
}