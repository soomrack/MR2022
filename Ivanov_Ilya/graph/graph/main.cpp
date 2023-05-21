#include "graph.h"

int main() {
    Graph a;
    a.add_node(2.00);
    a.add_node(3.00);
    a.add_node(6.00);
    a.print();
    a.add_edge(2.00, 6.00);
    a.add_edge(3.00, 6.00);
    a.print();
    a.del_edge(3.00, 6.00);
    a.del_node(3.00);
    a.print();
    return 0;
}
