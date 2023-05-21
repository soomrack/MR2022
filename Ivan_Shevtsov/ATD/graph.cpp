#include "graph.h"

using namespace graph_names;


Edge::Edge(Node *source, Node *target, int weight): source(source), target(target)
        , weight(weight){}

Edge::~Edge() {
    source = nullptr;
    target = nullptr;
    weight = 0;
}

bool Edge::operator==(const Edge &other) const {
    return (weight == other.weight and target == other.target and source == other.source);
}

Node::Node(double data): data(data){}

Node::Node(double data, Node *source, int weight) {
    this->data = data;
    Edge *newEdge = new Edge(source, this, weight);
    edges.push(newEdge);
}

Node::~Node() {
    data = 0;
    edges.clear();  // Q: вот тут же не нужно удалять каждую связь, для них же вызовется деструктор сам?
}

void Node::add_edge(Node *target, int weight) {
    Edge *newEdge = new Edge(this, target, weight);
    edges.push(newEdge);
}

int Node::del_edge(Node *target, int weight, bool delete_only_one_flag) {
    /**
     * @return number of remotes edges
     */

    Edge* tmpEdge = new Edge(this, target, weight);

    int deleted_edges_counter = 0;
    if (delete_only_one_flag) {
        if (edges.find_and_delete(tmpEdge)){
            return 1;
        } else { return 0; }
    }else {
        while (edges.find_and_delete(tmpEdge)){
            deleted_edges_counter++;
        }
    }

    delete tmpEdge;
    return deleted_edges_counter;
}

Graph::Graph(Node *root) {
    nodes.push(root);  // todo: push all the nodes in root edges
}

Graph::Graph(double data) {
    Node* newNode = new Node(data);
    nodes.push(newNode);
}

void Graph::add_node(Node* newNode) {
    nodes.push(newNode);
}

void Graph::add_edge(Node *source, Node *target, int weight) {
    source->add_edge(target, weight);
}

int Graph::del_node(double data, bool delete_only_one_flag) {
    /**
    * @return number of remotes nodes in graph
    */

    int deleted_nodes_counter = 0;
    auto* tmpNode = new Node(data);
    if (delete_only_one_flag){
        if (!nodes.find_and_delete(tmpNode)) {return 0;}
        deleted_nodes_counter++;
        for (auto &&node: nodes){
            for (auto it = node->edges.begin(); it != node->edges.end(); ++it){

                if (it.current_node->data->target->data == data){
                    auto tmp = it.current_node->p_next;
                    del_edge(node, it.current_node->data->target, it.current_node->data->weight);
                    it.current_node = tmp;
                }
            }
        }
    } else {
        while (nodes.find_and_delete(tmpNode)){
            if (!nodes.find_and_delete(tmpNode)) {return 0;}
            deleted_nodes_counter++;
            for (auto &&node: nodes){
                for (auto it = node->edges.begin(); it != node->edges.end(); ++it){
                    if (it.current_node->data->target->data == data){
                        auto tmp = it.current_node->p_next;
                        del_edge(node, it.current_node->data->target, it.current_node->data->weight);
                        it.current_node = tmp;
                    }
                }
            }
        }
    }
    return deleted_nodes_counter;
}

int Graph::del_edge(Node *source, Node *target, int weight, bool delete_only_one_flag) {
    return source->del_edge(target, weight, delete_only_one_flag);
}

void Graph::clear() {
    nodes.clear();
}

void Graph::show() {
    unsigned idx = 0;
    for (auto nodes_iterator = nodes.begin(); nodes_iterator != nodes.end(); ++nodes_iterator){
        std::cout << idx << ". Data: " << nodes_iterator.current_node->data->data << "\n" << "EDGES TO NODE:\n";

        // I understand that the loop in the loop is not good ( O(n^2) ),
        // but I think in the output you can allow such a luxury

        if (nodes_iterator.current_node->data->edges.is_empty()) {
            std::cout << "\tEMPTY\n";
            idx++;
            continue;
        }
        for (auto edges_iterator = nodes_iterator.current_node->data->edges.begin();
                edges_iterator != nodes_iterator.current_node->data->edges.end(); ++edges_iterator){
            std::cout << "\tdata: " << edges_iterator.current_node->data->target->data;
            std::cout << " weight: " << edges_iterator.current_node->data->weight << "\n";
            idx++;
        }
    }
    std::cout << "END OF GRAPH\n";
}

Graph::dijkstra_node* Graph::dijkstra_simple(Node *start_node, Node *target_node, bool show_log) {
    // Cast nodes list to struct list
    list_names::list<dijkstra_node*> dijkstra_data_list;
    for (auto it_nodes = nodes.begin(); it_nodes != nodes.end(); ++it_nodes){
        dijkstra_node* newObject = new dijkstra_node(it_nodes.current_node->data,
                                                    INT_MAX - 100, false,
                                                     find_dijkstra_node(dijkstra_data_list, start_node));
        // TODO: fix max dijkstra value
        dijkstra_data_list.push(newObject);
    }

    find_dijkstra_node(dijkstra_data_list, start_node)->dist = 0;

    if (show_log){
        std::cout << "WAYS FROM NODE WITH DATA: " << start_node->data <<
                    " TO NODE WITH DATA: " << target_node->data << "\n";
        for (auto it = dijkstra_data_list.begin(); it != dijkstra_data_list.end(); ++it){
            std::cout << it.current_node->data->node->data << "\t";
        }
        std::cout << "\n";
        for (auto it = dijkstra_data_list.begin(); it != dijkstra_data_list.end(); ++it){
            if (it.current_node->data->dist == INT_MAX - 100){
                std::cout << "INF" << "\t";
            } else {
                std::cout << it.current_node->data->dist << "\t";
            }
        }
        std::cout << "\n";
    }

    dijkstra_node* running_dijkstra_node = find_dijkstra_node(dijkstra_data_list, start_node);
    while (running_dijkstra_node != nullptr){
        running_dijkstra_node->visited = true;
        for (auto it_edge = running_dijkstra_node->node->edges.begin();
                it_edge != running_dijkstra_node->node->edges.end(); ++it_edge) {
            auto target_dijkstra_node = find_dijkstra_node(dijkstra_data_list,
                                                           it_edge.current_node->data->target);
            if (target_dijkstra_node->dist >
                running_dijkstra_node->dist + it_edge.current_node->data->weight)
            {
                target_dijkstra_node->dist = running_dijkstra_node->dist + it_edge.current_node->data->weight;
                target_dijkstra_node->prev = running_dijkstra_node;
            }
        }

        running_dijkstra_node = find_dijkstra_node_with_min_dist(dijkstra_data_list, show_log);
    }

    return find_dijkstra_node(dijkstra_data_list, target_node);
}

Graph::dijkstra_node *Graph::find_dijkstra_node(list_names::list<dijkstra_node *> &list, Node *find_node) {
    {
        for (auto it = list.begin(); it != list.end(); ++it){
            if (it.current_node->data->node == find_node){
                return it.current_node->data;
            }
        }
        return nullptr;
    }
}

Graph::dijkstra_node *
Graph::find_dijkstra_node_with_min_dist(list_names::list<dijkstra_node *> &list, bool print_value) {
    {
        int min = INT_MAX;
        dijkstra_node* ans = nullptr;
        for (auto it = list.begin(); it != list.end(); ++it){
            if (it.current_node->data->dist < min and !it.current_node->data->visited){
                min = it.current_node->data->dist;
                ans = it.current_node->data;
            }
        }
        if (print_value){
            for (auto it = list.begin(); it != list.end(); ++it){
                if (it.current_node->data->dist == INT_MAX - 100){
                    std::cout << "INF" << "\t";
                } else {
                    std::cout << it.current_node->data->dist << "\t";
                }
            }
            std::cout << "\n";
        }
        return ans;
    }
}

Graph::AStar_node*
Graph::AStar_simple(Node *source_node, double source_x, double source_y,
                    Node *target_node, double target_x, double target_y,
                    DynArr_names::dynamic_array<double>& x_array, DynArr_names::dynamic_array<double>& y_array) {
    // this func only for test, it will delete TODO
    list_names::list<AStar_node*> AStar_nodes_list;
    auto it = nodes.begin();
    for (int idx = 0; idx < nodes.lenght(); idx ++, ++it){
        AStar_node* newObject = new AStar_node(it.current_node->data,
                                               x_array[idx],
                                               y_array[idx]);
        AStar_nodes_list.push(newObject);
    }



    AStar_node* source = new AStar_node(source_node, source_x, source_y);
    AStar_node* target = new AStar_node(target_node, target_x, target_y);

    queue_names::queue<AStar_node*> open;
    queue_names::queue<AStar_node*> closed;

    open.push(source);

    while (!open.is_empty()){
        auto head_of_open = open.front()->data;
        open.pop();

        if (closed.value_in_queue(head_of_open)){
            continue;
        }

        if (head_of_open == target)
            return head_of_open;

        closed.push(head_of_open);

        for (auto it = AStar_nodes_list.begin(); it !=){
            open.push(AStar_nodes_list.return_node(it.current_node->data));

        }


    }


    return nullptr;
}


