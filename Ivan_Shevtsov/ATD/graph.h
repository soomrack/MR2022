//
// Created by ivan on 03/04/23.
//

#ifndef ATD_GRAPH_H
#define ATD_GRAPH_H
#include "iostream"
#include "vector"
#include <unordered_map>

namespace graph_names {
    class graph_exceptions: public std::domain_error{
    public:
        graph_exceptions(const char* massage): std::domain_error(massage){}
    };

    /**
     * @brief 2
     * @param 1 33
    */

/*    graph_exceptions ZERO_SIZE("zero size error");
    graph_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    graph_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    graph_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");*/
    enum edge_state{
        DOUBLE_LINKED = 1,
        FORWARD_LINKED = 2,
        BACK_LINKED = 3
    };

    class Node;
    typedef std::unordered_map<Node*, int> dict;

    class Node{
    public:
        double data;
        dict edges;

        Node* add_edge(Node* other_node_pointer, unsigned weight, edge_state = FORWARD_LINKED);

        Node(double data, Node* edge, unsigned edge_weight);
        Node(double data, vector_nodes_pointers edges_array, vector_int edge_weights);
    };

    class Graph {
    private:
        typedef std::vector<Node*> vector_nodes_pointers;
        vector_nodes_pointers nodes;
    public:
        Graph();
        Graph(double value);

        void add_node(double data);
        void add_edge(Node* first_node, Node* second_node, int weight, edge_state = FORWARD_LINKED);
        void delete_node(double data);
        void delete_edge(Node* first_node, Node* second_node);

        void show();
        void clear();

        ~Graph();
    };



} // graph_names

#endif //ATD_GRAPH_H
