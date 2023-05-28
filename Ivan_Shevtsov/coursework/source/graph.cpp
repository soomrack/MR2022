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


BaseGraph::BaseGraph(Node *root) {
    nodes.push(root);  // todo: push all the nodes in root edges
}

BaseGraph::BaseGraph(double data) {
    Node* newNode = new Node(data);
    nodes.push(newNode);
}

void BaseGraph::add_node(Node* newNode) {
    nodes.push(newNode);
}

void BaseGraph::add_edge(Node *source, Node *target, int weight) {
    source->add_edge(target, weight);
}

int BaseGraph::del_node(double data, bool delete_only_one_flag) {
    /**
    * @return number of remotes nodes in BaseGraph
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

int BaseGraph::del_edge(Node *source, Node *target, int weight, bool delete_only_one_flag) {
    return source->del_edge(target, weight, delete_only_one_flag);
}

void BaseGraph::clear() {
    nodes.clear();
}

void BaseGraph::show() {
    unsigned idx = 0;
    for (auto nodes_iterator = nodes.begin(); nodes_iterator != nodes.end(); ++nodes_iterator){
        std::cout << idx << ". Data: " << nodes_iterator.current_node->data->data << "\n" << "EDGES TO NODE:\n";

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
    std::cout << "END OF Graph\n";
}

void DijkstraGraph::naive_Dijkstra_search(Node *source, Node *target, bool show_log) {
    // mark source as visited
    source->dist = 0;
    source->visited = true;

    if (show_log){
        // DESCRIPTION
        std::cout << "WAYS FROM NODE WITH DATA: " << source->data <<
                  " TO NODE WITH DATA: " << target->data << "\n";

        // PRINT DATA
        for (auto it = nodes.begin(); it != nodes.end(); ++it){
            std::cout << it.current_node->data << "\t";
        }
        std::cout << "\n";

        // PRINT DIST
        for (auto it = nodes.begin(); it != nodes.end(); ++it){
            if (it.current_node->data->dist == INT_MAX - 100){
                std::cout << "INF" << "\t";
            } else {
                std::cout << it.current_node->data->dist << "\t";
            }
        }
        std::cout << "\n";
    }

    // MAIN ALGORITHM
    Node* running_node = source;
    while (running_node != nullptr){
        running_node->visited = true;  // mark node as visited
        for (auto it_edge = running_node->edges.begin();
                  it_edge != running_node->edges.end();
                  ++it_edge)
        {
            auto edge_target_node = it_edge.current_node->data->target;
            if (it_edge.current_node->data->target->dist >
                running_node->dist + it_edge.current_node->data->weight)
            {
                edge_target_node->dist = running_node->dist + it_edge.current_node->data->weight;
                edge_target_node->from = running_node;
            }
        }
        // integration across all nodes and choosing the minimum path
        running_node = find_node_with_min_dist(show_log);
    }
}

// Checks all the edges of node :(
Node *DijkstraGraph::find_node_with_min_dist(bool print_value) {
    int min = INT_MAX;
    Node* ans = nullptr;

    for (auto it = nodes.begin(); it != nodes.end(); ++it){
        if (!it.current_node->data->visited and it.current_node->data->dist < min){
            min = it.current_node->data->dist;
            ans = it.current_node->data;
        }
    }

    if (print_value){
        for (auto it = nodes.begin(); it != nodes.end(); ++it){
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

void Node::restore_path(DynArr_names::dynamic_array<double>& Empty, ALGORITHM_TYPE TYPE) {
    Node* running_node = this;
    if (TYPE == DIJKSTRA) {
        while (running_node != nullptr) {
            Empty.push_back(running_node->data);
            running_node = running_node->from;
        }
    }

    if (TYPE == ASTAR){
        while (running_node != nullptr) {
            Empty.push_back(running_node->data);
            running_node = running_node->fromNode;
        }
    }

    if (TYPE == LEE){
        while (running_node != nullptr) {
            Empty.push_back(running_node->data);
            running_node = running_node->fromNodeLee;
        }
    }
}

double Node::get_dist(const Node &target) {
    return sqrt(pow(target.x_pos - x_pos, 2) + pow(target.y_pos - y_pos, 2));
}

int Node::return_dist(ALGORITHM_TYPE TYPE) {
    if (TYPE == DIJKSTRA)   { return dist;}
    if (TYPE == ASTAR   )   { return distSource;}
    if (TYPE == LEE     )   {
        auto runningNode = fromNodeLee;
        unsigned counter = 1;
        while (runningNode->fromNodeLee != nullptr){
            counter++;
            runningNode = runningNode->fromNodeLee;
        }
        return counter;

    }
}

bool AStarGraph::AStarSearch(Node &source, Node &target, bool show_log) {
    list_names::list<Node*> closed;
    priority_queue_names::PriorityQueue<Node*, double> opened;

    // source node
    source.distSource = 0;
    source.distTargetEstimate = source.distSource + source.get_dist(target);

    opened.push(&source, source.distTargetEstimate);


    while (!opened.is_empty())
    {
        // check element of opened with min target dist
        Node* current_node = opened.back()->value;
        if ( current_node->x_pos == target.x_pos and current_node->y_pos == target.y_pos )
            return true;
        closed.push(current_node);
        opened.pop_min();

        // check neighbours
        for (auto current_edge : current_node->edges)
        {
            auto neighbour_node = current_edge->target;

            if (closed.is_in_list(neighbour_node)) {
                continue;}

            auto tmp_distNeighbourSource = current_node->distSource + current_edge->weight;

            if (!opened.is_data_in_queue(neighbour_node, neighbour_node->distTargetEstimate
                or tmp_distNeighbourSource < neighbour_node->distSource)){
                neighbour_node->fromNode = current_node;
                neighbour_node->distSource = tmp_distNeighbourSource;
                neighbour_node->distTargetEstimate = neighbour_node->distSource + neighbour_node->get_dist(target);
            }

            if (!opened.is_data_in_queue(neighbour_node, neighbour_node->distTargetEstimate)){
                opened.push(neighbour_node, neighbour_node->distTargetEstimate);
            }

        }
    }
    return false;
}

bool LeeGraph::LeeSearch(Node &source, Node &target) {

    // TODO источник должен быть первым в списке нод
    for (auto nodeIt = nodes.begin(); nodeIt != nodes.end(); ++nodeIt){
        auto running_node = nodeIt.current_node->data;
        for (auto it = running_node->edges.begin(); it != running_node->edges.end(); ++it) {
            if (it.current_node->data->target->fromNodeLee == nullptr){
                it.current_node->data->target->fromNodeLee = running_node;
            }
            if (it.current_node->data->target == &target) {
                source.fromNodeLee = nullptr;
                return true;
            }
        }
    }
    source.fromNodeLee = nullptr;
    return false;

}
