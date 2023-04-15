//
// Created by ivan on 03/04/23.
//

#ifndef ATD_GRAPH_H
#define ATD_GRAPH_H
#include "iostream"
#include "list.h"
#include <limits.h> // for int max func


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

    // CONSTANTS


    class Edge;
    class Node;
    class Graph;

    // EDGE
    class Edge{
    private:
        Node* source;
        Node* target;
        int weight;
    public:
        Edge(Node* source, Node* target, int weight);
        ~Edge() = default;
    public:
        friend Graph;
        friend Node;
    };


    // NODE
    class Node{
    private:
        list_names::list<Edge*> edges;
    public:
        double data;
    public:
        Node()=default;
        explicit Node(double data = 0);
        Node(double data, Node* source, int weight);
        ~Node();
    public:
        Node* add_edge(Node* target, int weight);
        Node* del_edge(Node* target, int weight);
    public:
        friend Graph;
    };


    //GRAPH
    typedef list_names::list<Node*> LISTOFNODES;
    class Graph {
    private:
        LISTOFNODES nodes;
        static const int INF = INT_MAX; // big const for Dijkstra`s algorithm
    public:
        Graph();
        Graph(Node* root);
        Graph(double data);
        ~Graph() {clear();};
    public:
        bool add_node(double data);
        bool add_edge(Node* link_from_this, Node* link_in_this, int weight);
        bool del_node(double data);  // add bool FLAG_DELL_ALL_WITH_DATA = true #todo
        bool del_edge(Node* first_node, Node* second_node);

        //void show();
        void clear();
    public:
        Graph& dijkstra_algorithm(Node* start_node, Node* target_node);

    };



} // graph_names

#endif //ATD_GRAPH_H
