#include "graph.h"

#include <vector>
#include <queue>

Graph::Graph(int verticesCount) : adj_(verticesCount), path_heuristics(verticesCount) {}

void Graph::addEdge(int src, int dest, int weight) {
    adj_[src].emplace_back(src, dest, weight);
}

std::vector<int> buildPath(std::vector<int> prev, int goal) {
    std::vector<int> path;
    for (int at = goal; at != -1; at = prev[at]) {
        path.push_back(at);
    }

    std::reverse(path.begin(), path.end());
    return path;
}

std::pair<std::vector<int>, Statistics> Graph::dijkstra(int start, int goal) const {
    std::vector<int> dist(verticesCount(), INT_MAX);
    std::vector<int> prev(verticesCount(), -1);
    std::vector<bool> visited(verticesCount(), false);
    dist[start] = 0;

    size_t touched_vertices = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto [current_dist, current] = pq.top();
        pq.pop();
        visited.emplace_back(true);
        ++touched_vertices;

        if (current == goal) {
            return {buildPath(prev, goal), {touched_vertices}};
        }

        for (const Edge& edge : adj_[current]) {
            if (dist[edge.src] + edge.weight < dist[edge.dest]) {
                dist[edge.dest] = dist[edge.src] + edge.weight;
                prev[edge.dest] = edge.src;

                if (!visited[edge.dest]) {
                    pq.emplace(dist[edge.dest], edge.dest);
                }
            }
        }
    }

    return {};
}

std::pair<std::vector<int>, Statistics> Graph::aStar(int start, int goal) const {
    std::vector<int> gScore(verticesCount(), INT_MAX);
    std::vector<int> fScore(verticesCount(), INT_MAX);
    std::vector<int> prev(verticesCount(), -1);
    std::vector<bool> visited(verticesCount(), false);

    gScore[start] = 0;
    fScore[start] = path_heuristics[start];

    size_t touched_vertices = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;
    pq.emplace(fScore[start], start);

    while (!pq.empty()) {
        auto [current_fScore, current] = pq.top();
        pq.pop();
        visited[current] = true;
        ++touched_vertices;

        if (current == goal) {
            return {buildPath(prev, goal), {touched_vertices}};
        }

        for (Edge edge : adj_[current]) {
            if (gScore[current] + edge.weight < gScore[edge.dest]) {
                prev[edge.dest] = current;
                gScore[edge.dest] = gScore[current] + edge.weight;
                fScore[edge.dest] = gScore[current] + edge.weight + path_heuristics[edge.dest];

                if (!visited[edge.dest]) {
                    pq.emplace(fScore[edge.dest], edge.dest);
                }
            }
        }
    }

    return {};
}
void Graph::addHeuristic(int v, int heuristic) {
    path_heuristics[v] = heuristic;
}
size_t Graph::verticesCount() const {
    return adj_.size();
}
