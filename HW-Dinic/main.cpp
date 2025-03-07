#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <algorithm>

std::unordered_map<char, int> charToIndex = {
    {'S', 0},
    {'A', 1},
    {'D', 2},
    {'G', 3},
    {'B', 4},
    {'E', 5},
    {'H', 6},
    {'C', 7},
    {'F', 8},
    {'I', 9},
    {'T', 10}
};

struct Edge {
  int dest, flow, capacity, rev;

  Edge(int dest, int capacity, int rev)
      : dest(dest), flow(0), capacity(capacity), rev(rev) {}
};

class Dinic {
 public:
  std::vector<std::vector<Edge>> adjList;
  std::vector<int> level;
  std::vector<size_t> ptr;
  int n;

  Dinic(int n) : n(n) {
      adjList.resize(n);
      level.resize(n);
      ptr.resize(n);
  }

  void addEdge(int src, int dest, int capacity) {
      adjList[src].emplace_back(dest, capacity, adjList[dest].size());
      adjList[dest].emplace_back(src, 0, adjList[src].size() - 1);
  }

  bool bfs(int s, int t) {
      level.assign(n, -1);
      std::queue<int> q;
      q.push(s);
      level[s] = 0;

      while (!q.empty()) {
          int u = q.front();
          q.pop();

          for (const Edge& e : adjList[u]) {
              if (level[e.dest] == -1 && e.flow < e.capacity) {
                  level[e.dest] = level[u] + 1;
                  q.push(e.dest);
              }
          }
      }
      return level[t] != -1;
  }

  int dfs(int u, int t, int flow) {
      if (u == t || flow == 0)
          return flow;

      for (size_t& i = ptr[u]; i < adjList[u].size(); ++i) {
          Edge& e = adjList[u][i];

          if (level[e.dest] == level[u] + 1 && e.flow < e.capacity) {
              int minFlow = std::min(flow, e.capacity - e.flow);
              int bottleNeck = dfs(e.dest, t, minFlow);

              if (bottleNeck > 0) {
                  e.flow += bottleNeck;
                  adjList[e.dest][e.rev].flow -= bottleNeck;
                  return bottleNeck;
              }
          }
      }

      return 0;
  }

  int maxFlow(int s, int t) {
      int max_flow = 0;

      while (bfs(s, t)) {
          ptr.assign(n, 0);
          int bottleNeck;
          while ((bottleNeck = dfs(s, t, INT_MAX)) > 0) {
              max_flow += bottleNeck;
          }
      }

      return max_flow;
  }
};


int main() {
    int n = charToIndex.size();
    Dinic dinic(n);

    dinic.addEdge(charToIndex['S'], charToIndex['A'], 5);
    dinic.addEdge(charToIndex['S'], charToIndex['D'], 10);
    dinic.addEdge(charToIndex['S'], charToIndex['G'], 15);
    dinic.addEdge(charToIndex['D'], charToIndex['A'], 15);

    dinic.addEdge(charToIndex['A'], charToIndex['B'], 10);
    dinic.addEdge(charToIndex['B'], charToIndex['E'], 25);
    dinic.addEdge(charToIndex['D'], charToIndex['E'], 5);
    dinic.addEdge(charToIndex['E'], charToIndex['G'], 5);
    dinic.addEdge(charToIndex['G'], charToIndex['H'], 5);

    dinic.addEdge(charToIndex['B'], charToIndex['C'], 10);
    dinic.addEdge(charToIndex['F'], charToIndex['B'], 15);
    dinic.addEdge(charToIndex['E'], charToIndex['F'], 30);
    dinic.addEdge(charToIndex['H'], charToIndex['F'], 5);
    dinic.addEdge(charToIndex['H'], charToIndex['I'], 10);

    dinic.addEdge(charToIndex['F'], charToIndex['I'], 15);

    dinic.addEdge(charToIndex['C'], charToIndex['T'], 5);
    dinic.addEdge(charToIndex['F'], charToIndex['T'], 15);
    dinic.addEdge(charToIndex['I'], charToIndex['T'], 10);

    std::cout << dinic.maxFlow(charToIndex['S'], charToIndex['T']) << '\n';

    return 0;
}
