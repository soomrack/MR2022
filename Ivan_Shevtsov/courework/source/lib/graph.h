#ifndef ATD_BaseGRAPH_H
#define ATD_BaseGRAPH_H
#include "iostream"
#include "list.h"
#include "dynamic_array.h"
#include "queue.h"
#include "priority_queue.h"
#include "BinaryHeap.h"
#include <climits> // for int max func
#include <cmath>


#ifndef ALGTYPE
#define ALGTYPE
enum ALGORITHM_TYPE{
    DIJKSTRA,
    ASTAR,
    LEE,
};
#endif


namespace graph_names {

    /**
     * @brief myGraph container
     */

    // DECLARATION
    class Edge;
    class Node;
    class BaseGraph;
    class DijkstraGraph;
    class AStarGraph;
    class LeeGraph;


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
    protected:
        // BASE EDGES
        list_names::list<Edge*> edges;

        // FOR DIJKSTRA
        // TODO find better wqy
        int dist     = INT_MAX - 100;
        bool visited = false;
        Node* from   = nullptr;

        // FOR A*
        double x_pos              = NAN;
        double y_pos              = NAN;
        double distSource         = INT_MAX - 100;  // set infinity distance from source
        double distTargetEstimate = INT_MAX - 100;  // estimate distance to target
        Node* fromNode            = nullptr;

        // FOR LEE
        Node* fromNodeLee         = nullptr;

    public:
        Node() = delete;
        // BASE CONSTRUCTOR
        explicit Node(double data = 0): data(data){};
        Node(double data, Node* source, int weight);
        // A* CONSTRUCTOR
        Node(double data, double x_pos, double y_pos): data(data), x_pos(x_pos), y_pos(y_pos) {};

        ~Node();
    public:
        void add_edge(Node* target, int weight);
        int del_edge(Node* target, int weight, bool delete_only_one_flag = false);
        bool operator==(Node const& other) const {return data == other.data;}
    public:
        void restore_path(DynArr_names::dynamic_array<double>& Empty, ALGORITHM_TYPE TYPE);
        int  return_dist(ALGORITHM_TYPE TYPE);

        double get_dist(const Node& target);
    public:
        friend BaseGraph;
        friend DijkstraGraph;
        friend AStarGraph;
        friend LeeGraph;
    };


    // GRAPH BASE
    class  BaseGraph {
    protected:
        list_names::list<Node*> nodes;
    public:
        // const INF = INT_MAX - 100; #TODO
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
        int get_size() {return nodes.lenght();}
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
        bool DijkstraSearch(Node& source, Node& target);

    };


    class AStarGraph:virtual public BaseGraph {
    private:

    public:
        AStarGraph() = default;
        AStarGraph(const DijkstraGraph&) = delete;
        AStarGraph& operator=(const DijkstraGraph&) = delete;
        ~AStarGraph() = default;
    public:
        bool AStarSearch(Node& source, Node& target, bool show_log = true);
    };


    class LeeGraph:virtual public BaseGraph {
    private:

    public:
        LeeGraph() = default;
        LeeGraph(const DijkstraGraph&) = delete;
        LeeGraph& operator=(const DijkstraGraph&) = delete;
        ~LeeGraph() = default;
    public:
        bool LeeSearch(Node& source, Node& target);
    };


    class Graph:
            virtual public AStarGraph,
            virtual public DijkstraGraph,
            virtual public LeeGraph
            {
    public:
        Graph() = default;
        ~Graph() = default;
        Graph(const Graph&) = delete;
        Graph& operator=(const Graph&) = delete;
    };

} // graph_names

#endif //ATD_GRAPH_H