//
// Created by ivan on 03/04/23.
// Oriented directed graph
//

#ifndef ATD_GRAPH_H
#define ATD_GRAPH_H
#include "iostream"
#include "list.h"
#include "dynamic_array.h"
#include "queue.h"
#include <limits.h> // for int max func
#include "math.h"


namespace graph_names {

    /**
     * @brief myGraph container
     *
     * use try/catch for work with graph
     *
     */

    // EXCEPTIONS
    class GraphException: public std::domain_error{
    public:
        GraphException(const char* massage): std::domain_error(massage){}
    };


    // DECLARATION

    class Edge;
    class Node;
    class Graph;

    // EDGE
    struct Edge{
        Node* source;
        Node* target;
        int weight;

        Edge(Node* source, Node* target, int weight);
        ~Edge();

        Edge() = delete;
        Edge(const Edge&) = delete;
        Edge& operator=(const Edge&) = delete;
        bool operator==(Edge const& other) const;
    };


    // NODE
    class Node{
    private:
        list_names::list<Edge*> edges;
    public:
        double data;
    public:
        Node() = delete;
        explicit Node(double data = 0);
        Node(double data, Node* source, int weight);
        ~Node();
    public:
        void add_edge(Node* target, int weight);
        int del_edge(Node* target, int weight, bool delete_only_one_flag = false);
        bool operator==(Node const& other) const {return data == other.data;}

    public:
        friend Graph;
    };


    //GRAPH
    class Graph {
    private:
        list_names::list<Node*> nodes;
    public:
        Graph() = default;
        explicit Graph(Node* root);
        explicit Graph(double data);
        Graph(const Graph&) = delete;
        Graph& operator=(const Graph&) = delete;
        ~Graph() {clear();}
    public:
        void add_node(Node* newNode);
        void add_edge(Node* source, Node* target, int weight);
        int del_node(double data, bool delete_only_one_flag = false);
        int del_edge(Node* source, Node* target, int weight, bool delete_only_one_flag = false);

        void show();
        void clear();
    };


} // graph_names

#endif //ATD_GRAPH_H