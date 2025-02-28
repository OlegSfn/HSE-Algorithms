#include "graph.h"
#include <unordered_map>
#include <iostream>

std::unordered_map<char, int> char_to_v = {
    {'S', 0},
    {'A', 1},
    {'B', 2},
    {'C', 3},
    {'E', 4},
    {'D', 5},
    {'F', 6},
    {'G', 7}
};

std::unordered_map<int, char> v_to_char = {
    {0, 'S'},
    {1, 'A'},
    {2, 'B'},
    {3, 'C'},
    {4, 'E'},
    {5, 'D'},
    {6, 'F'},
    {7, 'G'}
};

void build_graph(Graph& graph) {
    graph.addEdge(char_to_v['S'], char_to_v['A'], 6);
    graph.addEdge(char_to_v['S'], char_to_v['B'], 5);
    graph.addEdge(char_to_v['S'], char_to_v['B'], 10);

    graph.addEdge(char_to_v['A'], char_to_v['E'], 6);
    graph.addEdge(char_to_v['B'], char_to_v['E'], 6);
    graph.addEdge(char_to_v['B'], char_to_v['D'], 7);
    graph.addEdge(char_to_v['C'], char_to_v['D'], 6);

    graph.addEdge(char_to_v['E'], char_to_v['F'], 4);
    graph.addEdge(char_to_v['D'], char_to_v['F'], 6);

    graph.addEdge(char_to_v['F'], char_to_v['G'], 3);

    graph.addHeuristic(char_to_v['S'], 17);
    graph.addHeuristic(char_to_v['A'], 10);
    graph.addHeuristic(char_to_v['B'], 13);
    graph.addHeuristic(char_to_v['C'], 4);
    graph.addHeuristic(char_to_v['E'], 4);
    graph.addHeuristic(char_to_v['D'], 2);
    graph.addHeuristic(char_to_v['F'], 1);
    graph.addHeuristic(char_to_v['G'], 0);
}

int main() {
    Graph graph(8);
    build_graph(graph);

    std::pair<std::vector<int>, Statistics> path_a_star = graph.aStar(char_to_v['S'], char_to_v['G']);
    for (int v : path_a_star.first) {
        std::cout << v_to_char[v] << " ";
    }

    std::cout << "| " << path_a_star.second.touched_vertices;

    std::cout << "\n=================\n";

    std::pair<std::vector<int>, Statistics> path_dijkstra = graph.dijkstra(char_to_v['S'], char_to_v['G']);
    for (int v : path_dijkstra.first) {
        std::cout << v_to_char[v] << " ";
    }

    std::cout << "| " << path_a_star.second.touched_vertices << '\n';

    return 0;
}
