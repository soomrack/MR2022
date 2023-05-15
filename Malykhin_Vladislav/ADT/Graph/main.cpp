#include"Graph.h"


int main(){
    Graph graph = Graph();
    graph.add_node(1);
    graph.add_node(2);
    graph.add_node(3);
    graph.add_node(4);
    graph.add_node(5);
    graph.add_link(graph.get_node(1),graph.get_node(0));
    graph.add_link(graph.get_node(2),graph.get_node(0));
    graph.add_link(graph.get_node(2),graph.get_node(1));
    graph.add_link(graph.get_node(3),graph.get_node(2));
    graph.add_link(graph.get_node(0),graph.get_node(3));
    graph.add_link(graph.get_node(2),graph.get_node(3));
    graph.add_link(graph.get_node(0),graph.get_node(4));
    graph.add_link(graph.get_node(3),graph.get_node(4));
    graph.print();
    graph.get_node(0)->print();
    graph.get_node(1)->print();
    graph.get_node(2)->print();
    graph.get_node(3)->print();
    graph.get_node(4)->print();

}