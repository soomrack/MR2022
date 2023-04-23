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

    // DECLARATION

    class Edge;
    class Node;
    class Graph;
    class Path;

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

        bool visited = false;  // for Dijkstra`s algorithm
        int distance = INT_MAX;
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
        int get_distance() const{return distance;}
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
        int del_node(double data, bool delete_only_one_flag = false); // Q: вот это сделано отвратительно!
        int del_edge(Node* source, Node* target, int weight, bool delete_only_one_flag = false);

        void show();
        void clear();
    public:
        Path& dijkstra_algorithm(Node* source, Node* target);

    };

    class Path{
        list_names::list<Node*> path_nodes;
    public:
        Path() = delete;
        Path(Node* root);
        Path(const Path&) = delete;
        Path& operator=(const Path&) = delete;
        ~Path();

        void add_node(Node* target);
        int lenght() {return path_nodes.begin().current_node->data->get_distance();}
    };

} // graph_names

#endif //ATD_GRAPH_H
