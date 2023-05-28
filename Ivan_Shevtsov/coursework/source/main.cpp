#include <iostream>
#include "graph.h"

#ifndef ALGTYPE
#define ALG_TYPE
enum ALGORITHM_TYPE{
    DIJKSTRA,
    ASTAR,
    LEE,
};
#endif

// SEPARATOR
void sep(const char* message= "")
{
    std::cout << "----------------------------" << message << "----------------------------\n";
}

// TODO
void set_square_grid(graph_names::Graph& inputGraph, int x_max, int y_max, double step){
    using namespace graph_names;
    DynArr_names::dynamic_array<Node*> nodes(x_max * x_max);

    for (int layer = 0; layer < x_max; layer++){
        for(int nodeIdx = 0; nodeIdx < 2 * layer + 1; nodeIdx++){
            Node* newNode = new Node(0, layer, layer);
            nodes.push_back(newNode);
        }
        if (layer == 0){
            continue;
        }





    }


}

void test_Dijkstra(){
    using namespace graph_names;
    Graph graph1;
    sep("Dijkstra TEST STARTED");

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
    graph1.naive_Dijkstra_search(node1, node9, true);
    DynArr_names::dynamic_array<double> ans;
    node9->restore_path(ans, DIJKSTRA);
    std::cout << node9->return_dist(DIJKSTRA) << "\n";




}

void test_AStar(){

    sep("A* test");
    using namespace graph_names;
    Graph graph1;

    // input
    Node* node1   = new  Node(1 , 0.0, 0.0);
    Node* node2   = new  Node(2 , 1.0, 0.0);
    Node* node3   = new  Node(3 , 1.0, 1.0);
    Node* node4   = new  Node(4 , 1.0, 2.0);
    Node* node5   = new  Node(5 , 2.0, 2.0);
    Node* node6   = new  Node(6 , 2.0, 1.0);
    Node* node7   = new  Node(7 , 2.0, 0.0);
    Node* node8   = new  Node(8 , 3.0, 1.0);
    Node* node9   = new  Node(9 , 4.0, 2.0);
    Node* node10  = new  Node(10, 0.0, 0.0);
    Node* node11  = new  Node(11, 10.0,10.0);


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


    // test
    graph1.show();
    sep();


    sep("path");
    if (graph1.AStarSearch(*node1, *node9)) {
        DynArr_names::dynamic_array<double> ans;
        node9->restore_path(ans, ASTAR);
        std::cout << node9->return_dist(ASTAR) << "\n";
        ans.show();
    }
    else {
        std::cout << "FAILED" << "\n";
    }

}

void grid(graph_names::Graph& graph1, graph_names::Node* source, graph_names::Node* target){
    using namespace graph_names;

    // СЕТКА 5Х5
    auto node1 = source;
    auto node20  = target;
    //Node* node1   = new  Node(1);
    Node* node2   = new  Node(2 );
    Node* node3   = new  Node(3 );
    Node* node4   = new  Node(4 );
    Node* node5   = new  Node(5 );
    Node* node6   = new  Node(6 );
    Node* node7   = new  Node(7 );
    Node* node8   = new  Node(8 );
    Node* node9   = new  Node(9 );
    Node* node10  = new  Node(10);
    Node* node11  = new  Node(11);
    Node* node12  = new  Node(12);
    Node* node13  = new  Node(13);
    //Node* node14  = new  Node(1);
    Node* node15  = new   Node(15 );
    Node* node16  = new   Node(16 );
    Node* node17   = new  Node(17);
    Node* node18   = new  Node(18);
    Node* node19   = new  Node(19);
    //Node* node20  = new  Node(1);
    Node* node21  = new  Node(21);
    Node* node22  = new  Node(22);
    Node* node23  = new  Node(23);
    Node* node24  = new  Node(24);





    //graph1.add_node(node14);

    graph1.add_node(node24);
    graph1.add_node(node23);
    graph1.add_node(node22);
    graph1.add_node(node21);
    graph1.add_node(node20);
    graph1.add_node(node19);
    graph1.add_node(node18);
    graph1.add_node(node17);
    graph1.add_node(node16);
    graph1.add_node(node15);
    graph1.add_node(node13);
    graph1.add_node(node12);
    graph1.add_node(node11);
    graph1.add_node(node10);
    graph1.add_node(node9 );
    graph1.add_node(node8 );
    graph1.add_node(node7 );
    graph1.add_node(node6 );
    graph1.add_node(node5 );
    graph1.add_node(node4 );
    graph1.add_node(node3 );
    graph1.add_node(node2 );
    graph1.add_node(node1 );

    // УГЛЫ
    graph1.add_edge(node1, node2, 1);
    graph1.add_edge(node1, node3, 1);
    graph1.add_edge(node1, node4, 1);

    graph1.add_edge(node16, node9, 1);
    graph1.add_edge(node16, node10, 1);
    graph1.add_edge(node16, node17, 1);

    graph1.add_edge(node24, node15, 1);
    //graph1.add_edge(node24, node14, 1);
    graph1.add_edge(node24, node23, 1);

    graph1.add_edge(node20, node19, 1);
    graph1.add_edge(node20, node12, 1);
    graph1.add_edge(node20, node22, 1);

    // РЯДОМ С УГЛАМИ
    graph1.add_edge(node2, node1, 1);
    graph1.add_edge(node2, node3, 1);
    graph1.add_edge(node2, node4, 1);
    graph1.add_edge(node2, node5, 1);
    graph1.add_edge(node2, node6, 1);

    graph1.add_edge(node4, node1, 1);
    graph1.add_edge(node4, node3, 1);
    graph1.add_edge(node4, node2, 1);
    graph1.add_edge(node4, node7, 1);
    graph1.add_edge(node4, node8, 1);

    graph1.add_edge(node9, node16, 1);
    graph1.add_edge(node9, node17, 1);
    graph1.add_edge(node9, node10, 1);
    graph1.add_edge(node9, node5, 1);
    graph1.add_edge(node9, node6, 1);

    graph1.add_edge(node17, node16, 1);
    graph1.add_edge(node17, node9, 1);
    graph1.add_edge(node17, node10, 1);
    graph1.add_edge(node17, node11, 1);
    graph1.add_edge(node17, node18, 1);

    //graph1.add_edge(node15, node14, 1);
    //graph1.add_edge(node15, node23, 1); не скашиваем углы
    graph1.add_edge(node15, node24, 1);
    graph1.add_edge(node15, node7, 1);
    graph1.add_edge(node15, node8, 1);

    //graph1.add_edge(node23, node14, 1);
    graph1.add_edge(node23, node24, 1);
    graph1.add_edge(node23, node15, 1);
    graph1.add_edge(node23, node22, 1);
    graph1.add_edge(node23, node13, 1);

    graph1.add_edge(node19, node20, 1);
    graph1.add_edge(node19, node21, 1);
    graph1.add_edge(node19, node12, 1);
    graph1.add_edge(node19, node11, 1);
    graph1.add_edge(node19, node18, 1);

    graph1.add_edge(node21, node20, 1);
    graph1.add_edge(node21, node19, 1);
    graph1.add_edge(node21, node12, 1);
    graph1.add_edge(node21, node12, 1);
    graph1.add_edge(node21, node22, 1);



    graph1.add_edge(node22, node23, 1);
    graph1.add_edge(node22, node12, 1);
    graph1.add_edge(node22, node13, 1);
    graph1.add_edge(node22, node21, 1);
    //graph1.add_edge(node22, node14, 1);

    graph1.add_edge(node5, node2, 1);
    graph1.add_edge(node5, node3, 1);
    graph1.add_edge(node5, node6, 1);
    graph1.add_edge(node5, node9, 1);
    graph1.add_edge(node5, node10, 1);

    graph1.add_edge(node18, node17, 1);
    graph1.add_edge(node18, node19, 1);
    graph1.add_edge(node18, node11, 1);
    graph1.add_edge(node18, node12, 1);
    graph1.add_edge(node18, node10, 1);

    graph1.add_edge(node8, node3, 1);
    graph1.add_edge(node8, node4, 1);
    graph1.add_edge(node8, node7, 1);
    graph1.add_edge(node8, node15, 1);
    //graph1.add_edge(node8, node14, 1);



    // central graph1.add_edge(node3, node, 1);
    graph1.add_edge(node3, node1, 1);
    graph1.add_edge(node3, node2, 1);
    graph1.add_edge(node3, node4, 1);
    graph1.add_edge(node3, node5, 1);
    graph1.add_edge(node3, node6, 1);
    graph1.add_edge(node3, node7, 1);
    graph1.add_edge(node3, node8, 1);

    // central graph1.add_edge(node7, node, 1);
    graph1.add_edge(node7, node3, 1);
    graph1.add_edge(node7, node4, 1);
    //graph1.add_edge(node7, node6, 1); не скашиваем углы
    graph1.add_edge(node7, node8, 1);
    //graph1.add_edge(node7, node15, 1); не скашиваем углы
    //graph1.add_edge(node7, node14, 1); недоступно пройти
    //graph1.add_edge(node7, node13, 1); через стену нельзя

    // central graph1.add_edge(node6, node, 1);
    graph1.add_edge(node6, node3, 1);
    graph1.add_edge(node6, node2, 1);
    graph1.add_edge(node6, node9, 1);
    graph1.add_edge(node6, node5, 1);
    graph1.add_edge(node6, node10, 1);
    //graph1.add_edge(node6, node7, 1); не скашиваем углы
    //graph1.add_edge(node6, node11, 1); не скашиваем углы

    // central graph1.add_edge(node3, node, 1);
    graph1.add_edge(node10, node5, 1);
    graph1.add_edge(node10, node6, 1);
    graph1.add_edge(node10, node9, 1);
    graph1.add_edge(node10, node11, 1);
    graph1.add_edge(node10, node16, 1);
    graph1.add_edge(node10, node17, 1);
    graph1.add_edge(node10, node16, 1);

    // central graph1.add_edge(node3, node, 1);
    // graph1.add_edge(node11, node13, 1) не скашиаем углы;
    // graph1.add_edge(node11, node6, 1); не скашиаем углы
    graph1.add_edge(node11, node10, 1);
    graph1.add_edge(node11, node12, 1);
    graph1.add_edge(node11, node18, 1);
    graph1.add_edge(node11, node17, 1);
    graph1.add_edge(node11, node19, 1);

    // central graph1.add_edge(node3, node, 1);
    graph1.add_edge(node12, node22, 1);
    graph1.add_edge(node12, node21, 1);
    graph1.add_edge(node12, node20, 1);
    graph1.add_edge(node12, node11, 1);
    graph1.add_edge(node12, node13, 1);
    graph1.add_edge(node12, node18, 1);
    graph1.add_edge(node12, node19, 1);

    // central graph1.add_edge(node3, node, 1);
    //graph1.add_edge(node13, node11, 1); не скашиаем углы
    //graph1.add_edge(node13, node23, 1); не скашиаем углы
    graph1.add_edge(node13, node12, 1);
    graph1.add_edge(node13, node21, 1);
    graph1.add_edge(node13, node22, 1);
    //graph1.add_edge(node13, node14, 1); недоступно
    //graph1.add_edge(node13, node7, 1); недоступно

}


void test_Lee() {
    sep("Lee test");
    using namespace graph_names;
    Graph graph1;
    Node* source   = new  Node(1);
    Node* target   = new  Node(20);
    grid(graph1, source, target);


    sep("path");
    if (graph1.LeeSearch(*source, *target)) {
        DynArr_names::dynamic_array<double> ans;
        target->restore_path(ans, LEE);
        std::cout << target->return_dist(LEE) << "\n";
        ans.show();
    }
    else {
        std::cout << "FAILED" << "\n";
    }

}


int main() {
    //test_Dijkstra();
    //test_AStar();
    test_Lee();



    sep("GRAPH TEST ENDED");

    return 0;
}
