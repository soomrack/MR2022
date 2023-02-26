#include <iostream>


const unsigned int BASE_GRAPH_SIZE = 10;
const double COMPARATION_CONST = 0.0001;
const unsigned int MAX_WEIGHT = 4000000000;


double abs(double x){
    if (x < 0) return -x;
    return x;
}


struct item {
    double go_to;
    unsigned int weight;

    item();
    item(const double new_direction, const unsigned int new_weight);
};


struct node {
    double value;
    unsigned int amount;  // их количество
    item* data;  // список доступных для перемещения вершин

    node();
    node(const double vle);
    ~node();

    void add_item(const double new_direction, const unsigned int new_weight);
    unsigned int contain(const double to_go);
};


class Graph {

protected:
    unsigned int length;  // количество занятых мест
    node* Adjacency_list;  // места
    unsigned int size;  // количество всего мест


public:
    Graph();
    Graph(const double first_node);
    Graph(const unsigned int n, const double* names, const unsigned int* all_weights);
    ~Graph();

    node operator[](const double vle);

    void add_node(const double vle);
    void add_link_between(const double from, const double to, const unsigned int new_weight = 1, bool double_direction = false);

    unsigned int contains(const double vle);
    void output();

    unsigned int path_between(const double from, const double to);
};


item::item() {
    go_to = NULL;
    weight = NULL;
}


item::item(const double new_direction, const unsigned int new_weight) {
    go_to = new_direction;
    weight = new_weight;
}


node::node() {
    value = NULL;
    amount = 0;
    data = nullptr;
}


node::node(const double vle) {
    value = vle;
    amount = 0;
    data = nullptr;
}


node::~node() {
    data = nullptr;
}


void node::add_item(const double new_direction, const unsigned int new_weight) {
    item* temp = new item[amount + 1];
    for (unsigned int idx = 0; idx < amount; idx++){
        temp[idx] = data[idx];
    }
    temp[amount++] = item(new_direction, new_weight);
    data = nullptr;
    data = temp;
}


unsigned int node::contain(const double to_go) {
    for (unsigned int idx = 0; idx < amount; idx++){
        if (abs(data[idx].go_to - to_go) < COMPARATION_CONST) return idx + 1;
    }
    return 0;
}


Graph::Graph() {
    length = 0;
    size = 0;
    Adjacency_list = nullptr;
}


Graph::Graph(const double first_node) {
    length = 0;
    size = 0;
    Adjacency_list = nullptr;
    add_node(first_node);
}


Graph::Graph(const unsigned int n, const double *names, const unsigned int *weights) {
    // гарантируется, что размер names соответствует n, а weights - n * n;

    size = std::max(n, BASE_GRAPH_SIZE);
    length = 0;
    Adjacency_list = new node[size];

    for (unsigned int idx = 0; idx < n; idx++){
        add_node(names[idx]);
    }
    for (unsigned int idx = 0; idx < n; idx++) {
        for (unsigned int jdx = 0; jdx < n; jdx++) {
            if (weights[idx * n + jdx] == 0) continue;
            this->add_link_between(names[idx], names[jdx], weights[idx * n + jdx], false);
        }
    }

}


Graph::~Graph() {
    Adjacency_list = nullptr;
}


node Graph::operator[](const double vle) {
    for (unsigned int idx = 0; idx < length; idx++){
        if (abs(Adjacency_list[idx].value - vle) < COMPARATION_CONST) return Adjacency_list[idx];
    }
    return node();
}


void Graph::add_node(const double vle) {
    node new_node = node(vle);
    if (size == 0) {
        size = BASE_GRAPH_SIZE;
        Adjacency_list = new node[size];
    } else {
        if (length == size){
            size += BASE_GRAPH_SIZE;
            node* temp = new node[size];
            for (unsigned int idx = 0; idx < length; idx++){
                temp[idx] = Adjacency_list[idx];
            }
            Adjacency_list = nullptr;
            Adjacency_list = temp;
        }

    }
    Adjacency_list[length++] = new_node;

}


void Graph::add_link_between(const double from, const double to, const unsigned int new_weight, bool double_direction) {
    if (contains(from) == 0){
        add_node(from);
    }
    if (contains(to) == 0){
        add_node(to);
    }

    // позволяет строить кратные грани
    Adjacency_list[contains(from) - 1].add_item(to, new_weight);
    if (double_direction) Adjacency_list[contains(to) - 1].add_item(from, new_weight);
}


unsigned int Graph::contains(const double vle) {
    for (unsigned int idx = 0; idx < length; idx++){
        if (abs(Adjacency_list[idx].value - vle) < COMPARATION_CONST) return idx + 1;
    }
    return 0;
}


void Graph::output() {
    std::cout << "\nThe graph's size = " << size;
    if (size == 0){
        std::cout << "\n";
        return;
    }

    for (unsigned int idx = 0; idx < length; idx++){
        std::cout << "\nThe node " << Adjacency_list[idx].value;
        if (Adjacency_list[idx].amount == 0) continue;
        std::cout << " can goes to: ";
        for (unsigned int jdx = 0; jdx < Adjacency_list[idx].amount; jdx++){
            std::cout << Adjacency_list[idx].data[jdx].go_to << "(" << Adjacency_list[idx].data[jdx].weight << ") ";
        }

    }
    std::cout << "\nThus, graph includes " << length << "  item(s)\n";

}


unsigned int Graph::path_between(const double from, const double to) {
    unsigned int base_point = contains(from);
    if (base_point == 0) return 0;
    unsigned int final_point = contains(to);
    if (final_point == 0) return MAX_WEIGHT;

    // алгоритм Дейкстры

    bool* marked = new bool[length];
    for (unsigned int idx = 0; idx < length; idx++){
        marked[idx] = false;
    }
    marked[base_point - 1] = true;

    unsigned int* weights = new unsigned int [length];
    for (unsigned int idx = 0; idx < length; idx++){
        weights[idx] = MAX_WEIGHT;
    }
    for (unsigned int idx = 0; idx < Adjacency_list[base_point - 1].amount; idx++){
        weights[contains(Adjacency_list[base_point - 1].data[idx].go_to) - 1] = Adjacency_list[base_point - 1].data[idx].weight;
    }
    weights[base_point - 1] = 0;

    for (unsigned int loop = 0; loop < length; loop++){

        // поиск минимального непосещенного
        unsigned int min_of_wghts = MAX_WEIGHT;
        unsigned int idx_of_min = length;
        for (unsigned int idx = 0; idx < length; idx++){
            if (min_of_wghts > weights[idx] && !marked[idx]){
                min_of_wghts = weights[idx];
                idx_of_min = idx;
            }
        }

        marked[idx_of_min] = true;
        // нанесение новых весов
        for (unsigned int idx = 0; idx < Adjacency_list[idx_of_min].amount; idx++){
            if (marked[contains(Adjacency_list[idx_of_min].data[idx].go_to) - 1]) continue;

            weights[contains(Adjacency_list[idx_of_min].data[idx].go_to) - 1] = std::min(min_of_wghts + Adjacency_list[idx_of_min].data[idx].weight,
                                                                                         weights[contains(Adjacency_list[idx_of_min].data[idx].go_to) - 1]);
        }

    }


    return weights[final_point - 1];
}


int main() {

    Graph A = Graph();
    A.output();

    Graph B = Graph(0.1);
    B.output();

    B.add_node(1.2);
    B.output();

    std::cout << "\n" << B.contains(1.2) << "\n";

    B.add_link_between(1.2, 2.3, 5, true);
    B.output();

    unsigned int n = 5;
    double c_nodes[5] = {0.1, 1.2, 2.3, 3.4, 4.5};
    unsigned int c_weights[25] = {0, 50, 0, 0, 90,
                                  50, 0, 90, 0, 0,
                                  0, 90, 0, 80, 60,
                                  0, 0, 80, 0, 70,
                                  90, 0, 60, 70, 0};
    Graph C = Graph(n, c_nodes, c_weights);
    C.output();

    std::cout << "\n" << C.path_between(1.2, 4.5) << "\n";

    return 0;
}
