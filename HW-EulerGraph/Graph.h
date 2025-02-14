#pragma once
#include <vector>
#include <list>

class Graph {
 public:
  Graph(int verticesCount);

  void addEdge(int u, int v);
  bool isConnected();
  std::string checkEulerian();
  void printEulerTour();

 private:
  int verticesCount_;
  std::vector<std::list<int>> adj_;

  void dfs(int v, std::vector<bool>& visited, int& count);
  bool isBridge(int u, int v);
  void fleury(int u, std::vector<int>& path);
};
