#include <iostream>
#include "graph.h"


// SEPARATOR
void sep(const char* message= "")
{
    std::cout << "----------------------------" << message << "----------------------------\n";
}


void test_graph(){
    using namespace graph_names;
    Graph graph1;
    sep("GRAPH TEST STARTED");

    // input
    Node* node1 = new   Node(1.0);
    Node* node2 = new   Node(2);
    Node* node3 = new   Node(3);
    Node* node4 = new   Node(4);
    Node* node5 = new   Node(5);
    Node* node6 = new   Node(6);
    Node* node7 = new   Node(7);
    Node* node8  = new  Node(8 );
    Node* node9  = new  Node(9 );
    Node* node10  = new Node(10);
    Node* node11 = new  Node(11);


    graph1.add_node(node1);
    graph1.add_node(node2);
    graph1.add_node(node3);
    graph1.add_node(node4);
    graph1.add_node(node5);
    graph1.add_node(node6);
    graph1.add_node(node7);
    graph1.add_node(node8 );
    graph1.add_node(node9 );
    graph1.add_node(node10);
    graph1.add_node(node11);

    graph1.add_edge(node1, node2, 3);
    graph1.add_edge(node1, node3, 2);
    graph1.add_edge(node1, node4, 1);
    graph1.add_edge(node4, node5, 10);
    graph1.add_edge(node5, node5, 10);
    graph1.add_edge(node5, node9, 15);
    graph1.add_edge(node3, node6, 8);
    graph1.add_edge(node6, node5, 5);
    graph1.add_edge(node6, node8, 6);
    graph1.add_edge(node8, node9, 1);
    graph1.add_edge(node10, node8, 5);
    graph1.add_edge(node2, node7, 12);
    graph1.add_edge(node2, node6, 4);
    graph1.add_edge(node7, node6, 3);


    //Node* delNode1 = new Node(2);
    //Node* delNode2 = new Node(2);
    //graph1.add_node(delNode1);
    //graph1.add_node(delNode2);
    //graph1.add_edge(delNode1, delNode2, 2);
    //graph1.add_edge(delNode2, delNode1, 3);
    //graph1.add_edge(node2, delNode2, 4);
    //graph1.add_edge(node1, delNode1, 4);

    // test
    graph1.show();
    sep();
    //graph1.del_node(2, false);
    //graph1.show();
    sep("dijkstra test");
    sep("dijkstra path");
    graph1.find_DijkstraPath_simple(node1, node9, true);
    DynArr_names::dynamic_array<double> ans;
    node9->restore_path(ans);
    std::cout << node9->return_dist() << "\n";


    sep("A* test");
    // GENERATE GRID MANUALLY
    auto* x_array = new DynArr_names::dynamic_array<double>;
    auto* y_array = new DynArr_names::dynamic_array<double>;

    sep("GRAPH TEST ENDED");
}


int main() {
    test_graph();

    return 0;
}
