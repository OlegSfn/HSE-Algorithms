#include "Graph.h"

#include <iostream>
#include <algorithm>

Graph::Graph(int verticesCount) : verticesCount_(verticesCount), adj_(verticesCount_) {}

void Graph::addEdge(int u, int v) {
    adj_[u].push_back(v);
    adj_[v].push_back(u);
}

void Graph::dfs(int v, std::vector<bool>& visited, int& count) {
    visited[v] = true;
    ++count;
    for (int neighbor : adj_[v]) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited, count);
        }
    }
}

bool Graph::isConnected() {
    std::vector<bool> visited(verticesCount_, false);
    int i;
    for (i = 0; i < verticesCount_; ++i) {
        if (!adj_[i].empty()){
            break;
        }
    }

    if (i == verticesCount_) {
        return true;
    }

    int count = 0;
    dfs(i, visited, count);

    for (i = 0; i < verticesCount_; ++i) {
        if (!adj_[i].empty() && !visited[i]) {
            return false;
        }
    }

    return true;
}

std::string Graph::checkEulerian() {
    if (!isConnected()) {
        return "No Eulerian path or cycle (disconnected).";
    }

    int odd = 0;
    for (int i = 0; i < verticesCount_; ++i) {
        if (adj_[i].size() % 2 != 0) {
            ++odd;
        }
    }

    if (odd == 0) {
        return "Eulerian Cycle";
    }
    else if (odd == 2) {
        return "Eulerian Path";
    }

    return "No Eulerian path or cycle.";
}

bool Graph::isBridge(int u, int v) {
    std::vector<bool> visited(verticesCount_, false);
    int count1 = 0;
    dfs(u, visited, count1);

    adj_[u].remove(v);
    adj_[v].remove(u);

    std::fill(visited.begin(), visited.end(), false);
    int count2 = 0;
    dfs(u, visited, count2);

    adj_[u].push_back(v);
    adj_[v].push_back(u);

    return (count2 < count1);
}

void Graph::fleury(int u, std::vector<int>& path) {
    while (!adj_[u].empty()) {
        int v = -1;

        for (int w : adj_[u]) {
            if (adj_[u].size() == 1 || !isBridge(u, w)) {
                v = w;
                break;
            }
        }

        if (v == -1) {
            v = adj_[u].front();
        }

        adj_[u].remove(v);
        adj_[v].remove(u);

        fleury(v, path);
    }

    path.push_back(u);
}


void Graph::printEulerTour() {
    std::string result = checkEulerian();
    if (result != "Eulerian Cycle" && result != "Eulerian Path") {
        std::cout << result << '\n';
        return;
    }

    int start = 0;
    if (result == "Eulerian Path") {
        for (int i = 0; i < verticesCount_; ++i) {
            if (adj_[i].size() % 2 != 0) {
                start = i;
                break;
            }
        }
    } else {
        for (int i = 0; i < verticesCount_; ++i) {
            if (!adj_[i].empty()) {
                start = i;
                break;
            }
        }
    }

    std::vector<int> path;
    fleury(start, path);
    reverse(path.begin(), path.end());

    std::cout << "Euler tour: ";
    for (int node : path) {
        std::cout << node << " ";
    }
    std::cout << '\n';
}