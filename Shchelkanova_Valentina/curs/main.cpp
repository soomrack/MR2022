#include "graph.h"

int main() {
    Graph g;

    // Добавление вершин и ребер
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addEdge(1, 0, 10);
    g.addEdge(1, 2, 20);
    g.addEdge(0, 2, 30);


    // Использование алгоритма Прима
    g.primAlgorithm();

    g.kruskalAlgorithm();
    return 0;
}
