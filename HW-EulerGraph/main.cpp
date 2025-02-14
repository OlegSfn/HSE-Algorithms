#include "graph.h"

int main() {
    Graph g1(5);
    g1.addEdge(0,1);
    g1.addEdge(0,2);
    g1.addEdge(1,2);

    g1.addEdge(2,3);
    g1.addEdge(3,4);

    g1.printEulerTour();

    Graph g2(5);
    g2.addEdge(0,1);
    g2.addEdge(0,2);
    g2.addEdge(1,2);

    g2.addEdge(2,3);
    g2.addEdge(2,4);
    g2.addEdge(3,4);

    g2.printEulerTour();

    Graph g3(5);
    g3.addEdge(0,1);
    g3.addEdge(0,2);
    g3.addEdge(1,2);

    g3.addEdge(2,3);
    g3.addEdge(3,4);

    g3.addEdge(1,3);

    g3.printEulerTour();

    return 0;
}
