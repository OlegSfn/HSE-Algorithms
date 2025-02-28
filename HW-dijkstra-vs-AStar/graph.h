#pragma once
#include <vector>

struct Statistics {
  size_t touched_vertices;
};

struct Edge {
    int src, dest, weight;
    Edge() = default;
    Edge(int src, int dest, int weight) : src(src), dest(dest), weight(weight) {}
};

class Graph {
 public:
  Graph(int verticesCount);
  void addEdge(int src, int dest, int weight);
  void addHeuristic(int v, int heuristic);

  size_t verticesCount() const;

  std::pair<std::vector<int>, Statistics> dijkstra(int start, int goal) const;

  std::pair<std::vector<int>, Statistics> aStar(int start, int goal) const;

 private:
  std::vector<std::vector<Edge>> adj_;
  std::vector<int> path_heuristics;
};
