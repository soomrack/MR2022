#ifndef ATD_BaseGRAPH_H
#define ATD_BaseGRAPH_H
#include "iostream"
#include "list.h"
#include "dynamic_array.h"
#include "queue.h"
#include <climits> // for int max func
#include <cmath>


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
    class BaseGraph;
    class DijkstraGraph;
    class AStarGraph;


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
    struct Node{
        double data;
    private:
        list_names::list<Edge*> edges;

        // FOR DIJKSTRA
        // TODO find better wqy
        int dist     = INT_MAX - 100;
        bool visited = false;
        Node* from   = nullptr;

        // FOR A*
        double x_pos      = NAN;
        double y_pos      = NAN;
        double distSource = NAN;  // distance from source
        double distTarget = NAN;  // estimate distance to target
        Node* fromNode    = nullptr;

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
        void restore_path(DynArr_names::dynamic_array<double>& Empty);  // FOR DIJKSTRA
        int  return_dist() {return dist;}

        double get_dist(const Node& target);
    public:
        friend BaseGraph;
        friend DijkstraGraph;
        friend AStarGraph;
    };


    // GRAPH BASE
    class  BaseGraph {
    protected:
        list_names::list<Node*> nodes;

        //  PLANING
        DynArr_names::dynamic_array<Node*> Path;
    public:
        BaseGraph() = default;
        explicit BaseGraph(Node* root);
        explicit BaseGraph(double data);
        BaseGraph(const BaseGraph&) = delete;
        BaseGraph& operator=(const BaseGraph&) = delete;
        ~BaseGraph() {clear();}
    public:
        void add_node(Node* newNode);
        void add_edge(Node* source, Node* target, int weight);
        int del_node(double data, bool delete_only_one_flag = false);
        int del_edge(Node* source, Node* target, int weight, bool delete_only_one_flag = false);

        void show();
        void clear();
    };


    class DijkstraGraph:virtual public BaseGraph {
    private:
        Node* find_node_with_min_dist(bool print_value);
    public:
        DijkstraGraph() = default;
        DijkstraGraph(const DijkstraGraph&) = delete;
        DijkstraGraph& operator=(const DijkstraGraph&) = delete;
        ~DijkstraGraph() = default;
    public:
        void naive_Dijkstra_search(Node* source, Node* target, bool show_log = true);
    };


    class AStarGraph:virtual public BaseGraph {
    private:

    public:
        AStarGraph() = default;
        AStarGraph(const DijkstraGraph&) = delete;
        AStarGraph& operator=(const DijkstraGraph&) = delete;
        ~AStarGraph() = default;
    public:
        void AStarSearch(Node& source, Node& target);

    };


    class Graph:
            virtual public AStarGraph,
            virtual public DijkstraGraph{
    public:
        Graph() = default;
        ~Graph() = default;
        Graph(const Graph&) = delete;
        Graph& operator=(const Graph&) = delete;


    private:

    };

} // graph_names

#endif //ATD_GRAPH_H