//
// Created by ivan on 03/04/23.
//

#ifndef ATD_GRAPH_H
#define ATD_GRAPH_H
#include "iostream"
#include <vector>
#include <unordered_map>

namespace graph_names {

    /**
     * @brief Directed weighted graph
     *
     * Use block try/catch to work whits it, catch graph_exception type.
     *
    */

    // EXCEPTIONS
    class graph_exceptions: public std::domain_error{
    public:
        graph_exceptions(const char* massage): std::domain_error(massage){}
    };

/*    graph_exceptions ZERO_SIZE("zero size error");
    graph_exceptions QUEUE_OUT_OF_TRE_RANGE("index out of the range");
    graph_exceptions QUEUE_POP_ERROR("can`t pop from empty queue");
    graph_exceptions QUEUE_SHOW_ERROR("can`t show zero size queue");*/


    // EDGE
    enum edge_state{
        DOUBLE_LINKED,
        SINGLY_LINKED,
        NOT_LINKED
    };

    class Node;
    class Edge;
    class Graph;

    typedef std::vector<Edge*> vector_edges;
    typedef std::vector<Node*> vector_nodes_pointers;
    int START_VECTOR_NODES_SIZE = 50;  // start for edge vector size and node vector size
    int START_VECTOR_EDGES_SIZE = 10;
    int INFINITY = 2147483640;  // big const for Dijkstra`s algorithm

    class Edge{
    private:
        edge_state direction;
        Node* from_node;
        Node* in_node;
        int weight;
    public:
        friend Graph;
        friend Node;
        Edge(edge_state state, Node* from, Node* in, int weight) {
            direction = state;
            from_node = from;
            in_node = in;
            this->weight = weight; }
        ~Edge();
    };


    // NODE
    class Node{
    private:
        vector_edges edges;
        int node_id;

    public:
        friend Graph;
        double data;
        static int node_counter;  // for node id generator // todo: do it private

        Node() ;

        Node(const Node& other);
        Node& operator=(const Node& other){}  //#todo
        ~Node();

        Node(double data);
        Node(double data, Node* link_from_this, int edge_weight, edge_state state = SINGLY_LINKED);

        static int get_node_count(){ return node_counter; }
        int get_node_id() { return node_id; }
        void push_edge(Edge* edge){ edges.push_back(edge);}
        Node* add_edge(Node* link_from_this, int edge_weight, edge_state state = SINGLY_LINKED);
        Node* delete_edge(Node* linked_node);

    };

    int Node::node_counter = 0;




    //GRAPH
    class Graph {
    private:
        vector_nodes_pointers nodes;

    public:
        Graph();
        Graph(Node* root);
        Graph(double data);

        void add_node(double data);
        void add_edge(Node* link_from_this, Node* link_in_this, int weight, edge_state state = SINGLY_LINKED);
        void delete_node(double data);
        void delete_edge(Node* first_node, Node* second_node);
        int node_count() { return Node::get_node_count();}

        Graph& dijkstra_algorithm(Node* start_node, Node* target_node);

        //void show();
        void clear();

        ~Graph() {clear();};
    };



} // graph_names

#endif //ATD_GRAPH_H
