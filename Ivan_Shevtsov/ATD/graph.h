//
// Created by ivan on 03/04/23.
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
     *
     * @class GraphException has these exceptions(objects):
     *
     * @objects ... TODO here will be exception objects declarations
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
    public:
        // DIJKSTRA
        struct dijkstra_node{
            Node* node;
            int dist;
            bool visited;
            dijkstra_node* prev;

            dijkstra_node(Node* node, int dist, bool visited, dijkstra_node* prev): node(node), dist(dist),
                                                                           visited(visited), prev(prev){}
            DynArr_names::dynamic_array<double> restore_path (){
                DynArr_names::dynamic_array<double> path(10);

                dijkstra_node* running_node = this;
                while (running_node != nullptr){
                    path.push_back(running_node->node->data);
                    running_node = running_node->prev;
                }
                return path;
            }

            dijkstra_node(const dijkstra_node&) = delete;
            dijkstra_node& operator=(const dijkstra_node&) = delete;
            ~dijkstra_node() = default;

        };

        dijkstra_node* dijkstra_simple(Node* source, Node* target, bool show_log = true);
    private:
        dijkstra_node* find_dijkstra_node(list_names::list<dijkstra_node*>& list,Node* find_node);
        dijkstra_node* find_dijkstra_node_with_min_dist(list_names::list<dijkstra_node*>& list, bool print_value = false);


    public:
        // AStar
        struct AStar_node{
            Node* node;
            double x;
            double y;

            AStar_node(Node* node, double x, double y): node(node), x(x), y(y){};
            bool operator==(AStar_node const& other){
                return node == other.node and x == other.x and y == other.y;
            }

        };

        AStar_node* AStar_simple(Node* source_node, double source_x, double source_y,
                                Node* target_node, double target_x, double target_y,
                                 DynArr_names::dynamic_array<double>& x_array, DynArr_names::dynamic_array<double>& y_array);
        double find_heuristics(AStar_node* source, AStar_node* target){
            return sqrt(source->x * source->x + target->y * target->y);
        }
    };


} // graph_names

#endif //ATD_GRAPH_H