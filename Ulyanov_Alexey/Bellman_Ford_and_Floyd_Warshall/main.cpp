#include <iostream>
#include "algorithm"
#include "dynamic_array.h"


const int MAX_COUNT = 999999;
unsigned int kol = 0;


struct Way {
    unsigned int to;
    unsigned int from;
    unsigned int cost;
};


class Node {

public:
    unsigned int value;

    Dynamic_array<Node*> neighbors;
    Dynamic_array<int> weights;


public:

    Node();
    Node(const unsigned int x);
    Node(const Node& x);

    Node& operator=(const Node& x);
    friend bool operator== (const Node &x, const Node &y);

};


class Graph {

private:
    Dynamic_array<Node> vertexs;

    Dynamic_array<Way> ways;
    Dynamic_array<Dynamic_array<unsigned int>> adjacency_matrix;


public:

    void add_node(const unsigned int new_name);
    void add_path(const unsigned int from, const unsigned int to, const int cost, const bool add_reverse = false);

    bool contains(const unsigned int node_name);

    void del_node(const unsigned int name_to_del);
    void del_path(const unsigned int from, const unsigned int to);

    void generate_ways();
    void generate_matrix();

    Dynamic_array<unsigned int> Bellman_Ford(const unsigned int start);
    Dynamic_array<Dynamic_array<unsigned int>> Floyd_Warshall();

    void output(const bool flag = false);

private:

    Node* get(const unsigned int node_name);

};


Node::Node() {
    value = 0;
    neighbors = Dynamic_array<Node*>();
    weights = Dynamic_array<int>();
}


Node::Node(const unsigned int x) {
    value = x;
    neighbors = Dynamic_array<Node*>();
    weights = Dynamic_array<int>();
}


Node::Node(const Node &x) {
    value = x.value;
    neighbors = x.neighbors;
    weights = x.weights;
}


Node& Node::operator=(const Node &x) {
    value = x.value;
    neighbors = x.neighbors;
    weights = x.weights;
}


bool operator==(const Node &x, const Node &y) {
    if (x.value == y.value) return true;
    return false;
}


void Graph::add_node(const unsigned int new_name) {
    vertexs.push_back(Node(new_name));
}


void Graph::add_path(const unsigned int from, const unsigned int to, const int cost, const bool add_reverse) {
    if (!contains(from)) add_node(from);
    if (!contains(to)) add_node(to);

    Node* node_from = get(from);
    Node* node_to = get(to);

    unsigned int pos_of_to = node_from->neighbors.position(node_to);
    if (pos_of_to == 0) {
        node_from->neighbors.push_back(node_to);
        node_from->weights.push_back(cost);
    } else {
        node_from->weights[pos_of_to - 1] = std::min(node_from->weights[pos_of_to - 1], cost);
    }

    if (add_reverse){
        add_path(to, from, cost, false);
    }

}


void Graph::del_node(const unsigned int name_to_del) {
    Node * node_to_del = get(name_to_del);

    unsigned int pos_node_to_del_in_vertex = vertexs.position(*node_to_del);
    if (pos_node_to_del_in_vertex == 0) return;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        unsigned int pos_node_to_del_in_neighbours = vertexs[idx].neighbors.position(node_to_del);
        if (pos_node_to_del_in_neighbours == 0) continue;

        vertexs[idx].neighbors.del(pos_node_to_del_in_neighbours - 1);
        vertexs[idx].weights.del(pos_node_to_del_in_neighbours - 1);
    }

    vertexs.del(pos_node_to_del_in_vertex - 1);
}


void Graph::del_path(const unsigned int from, const unsigned int to) {
    unsigned int pos_node_from_in_vertex = vertexs.position(*get(from));
    if (pos_node_from_in_vertex == 0) return;

    unsigned int pos_node_to_in_froms_neighbours = vertexs[pos_node_from_in_vertex - 1].neighbors.position(get(to));
    if (pos_node_to_in_froms_neighbours == 0) return;

    vertexs[pos_node_from_in_vertex - 1].neighbors.del(pos_node_to_in_froms_neighbours - 1);
    vertexs[pos_node_from_in_vertex - 1].weights.del(pos_node_to_in_froms_neighbours - 1);

}


bool Graph::contains(const unsigned int node_name) {
    if (vertexs.length() == 0) return false;

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return true;
    }
    return false;
}


void Graph::output(const bool flag) {
    if (vertexs.length() == 0) {
        std::cout << "There is no elements in this graph\n\n";
        return;
    }

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        std::cout << vertexs[idx].value << "   [";

        if (vertexs[idx].neighbors.length() != 0){
            for (unsigned int jdx = 0; jdx < vertexs[idx].neighbors.length(); jdx++){
                std::cout << " " << vertexs[idx].neighbors[jdx]->value << "{" << vertexs[idx].weights[jdx] << "} ";
            }
        }

        std::cout << "]\n";
    }
    std::cout << "\n";

    if (flag){
        for (unsigned int idx = 0; idx < ways.length(); idx++){
            std::cout << ways[idx].from << "\t" << ways[idx].to << "\t" << ways[idx].cost << "\n";
        }
        std::cout << "\n";

        for (unsigned int idx = 0; idx < adjacency_matrix.length(); idx++){
            for (unsigned int jdx = 0; jdx < adjacency_matrix[idx].length(); jdx++){
                if (adjacency_matrix[idx][jdx] == MAX_COUNT)
                    std::cout << "*  ";
                else
                    std::cout << adjacency_matrix[idx][jdx] << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}


Node* Graph::get(const unsigned int node_name) {

    if (!contains(node_name)) return new Node();

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        if (vertexs[idx].value == node_name) return &vertexs[idx];
    }

    return new Node();
}


void Graph::generate_ways() {

    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        for (unsigned int jdx = 0; jdx < vertexs[idx].neighbors.length(); jdx++){
            Way new_way;
            new_way.from = vertexs[idx].value;
            new_way.to = vertexs[idx].neighbors[jdx]->value;
            new_way.cost = vertexs[idx].weights[jdx];

            ways.push_back(new_way);
        }
    }
}


void Graph::generate_matrix() {
    // init of adjacency_matrix
    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        adjacency_matrix.push_back(*new Dynamic_array<unsigned int>(vertexs.length()));
    }


    for (unsigned int idx = 0; idx < vertexs.length(); idx++){
        for (unsigned int jdx = 0; jdx < vertexs.length(); jdx++){
            adjacency_matrix[idx][jdx] = MAX_COUNT;
        }
        for (unsigned int jdx = 0; jdx < vertexs[idx].neighbors.length(); jdx++){
            adjacency_matrix[idx][vertexs[idx].neighbors[jdx]->value] = vertexs[idx].weights[jdx];
        }
        adjacency_matrix[idx][idx] = 0;
    }
}


Dynamic_array<unsigned int> Graph::Bellman_Ford(const unsigned int start) {

    // инициализация массива расстояний из вершины start
    Dynamic_array<unsigned int> ans = Dynamic_array<unsigned int>(vertexs.length());

    // он заполняется значениями, равными максимальной дистанции, то есть на нулевом этапе итераций все вершины считаются недостижимыми
    for (unsigned int idx = 0; idx < ans.length(); idx++){
        ans[idx] = MAX_COUNT;
    }

    // проверяется наличие данной вершины в графе
    // если её нет, то осуществляется выход из функции, иначе соответствующему значению массива присваивается 0
    if (!contains(start)) return ans;
    ans[start] = 0;

    // далее происходит заполнение массива с помощью списка ребер:
    // считается, что если путь до вершины i кратчайший, то путь до вершины j определится как сумма путей от start до i и от i до j
    // полагается, что за n итераций определятся все наикратчайшие пути до всех n вершин
    for (unsigned int idx = 0; idx < vertexs.length() - 1; idx++){
        for (unsigned int jdx = 0; jdx < ways.length(); jdx++){
            ans[ways[jdx].to] = std::min(ans[ways[jdx].to], ans[ways[jdx].from] + ways[jdx].cost);
        }
    }

    return ans;
}


Dynamic_array<Dynamic_array<unsigned int>> Graph::Floyd_Warshall() {

    // алгоритм Флойда-Уоршелла определяет наикратчайшие пути от всех вершин до всех
    // поэтому на нулевой итерации результирующая матрица соответствует матрице смежности
    Dynamic_array<Dynamic_array<unsigned int>> ans = adjacency_matrix;

    // далее для каждой k-ой вершины проверяется следующее:
    // какой из путей от i до j (напрямую или через вершину k (от i до k + от k до j)) минимальным
    for (unsigned int kdx = 0; kdx < vertexs.length(); kdx++){
        for (unsigned int row = 0; row < vertexs.length(); row++){
            for (unsigned int col = 0; col < vertexs.length(); col++){
                ans[row][col] = std::min(ans[row][col], ans[row][kdx] + ans[kdx][col]);
            }
        }
    }

    return ans;

}



void Bellman_Ford_test(Graph A){

    A.generate_ways();
    A.output(true);

    Dynamic_array<unsigned int> distance = A.Bellman_Ford(0);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(1);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(2);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(3);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(4);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(5);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";
    distance = A.Bellman_Ford(6);
    for (unsigned int idx = 0; idx < distance.length(); idx++){
        std::cout << distance[idx] << "  ";
    }
    std::cout << "\n";

    std::cout << "\n";
}


void Floyd_Warshall_test(Graph A){

    A.generate_matrix();
    A.output(true);

    Dynamic_array<Dynamic_array<unsigned int>> dist_matrix = A.Floyd_Warshall();
    for (unsigned int idx = 0; idx < dist_matrix.length(); idx++){
        for (unsigned int jdx = 0; jdx < dist_matrix[idx].length(); jdx++){
            if (dist_matrix[idx][jdx] == MAX_COUNT)
                std::cout << "*  ";
            else
                std::cout << dist_matrix[idx][jdx] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}


int main() {

    Graph A;
    A.add_node(kol++);
    A.add_node(kol++);
    A.add_node(kol++);
    A.add_node(kol++);
    A.add_node(kol++);
    A.add_node(kol++);
    A.add_node(kol++);

    A.add_path(0, 1, 4, true);
    A.add_path(0, 2, 3, true);
    A.add_path(1, 3, 2, true);
    A.add_path(1, 4, 2, true);
    A.add_path(2, 3, 3, true);
    A.add_path(3, 4, 1, true);
    A.add_path(3, 5, 4, true);
    A.add_path(4, 5, 6, true);
    A.add_path(5, 6, 3, true);

    A.output();

    Bellman_Ford_test(A);

    Floyd_Warshall_test(A);

    return 0;
}