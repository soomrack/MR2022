#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Node { // класс Node
public:
    int node;
    vector<int> edges;
    Node(int node) {
        this->node = node;
    }
};

class Graph {
    vector<Node> nodes; // список вершин
public:
    Graph();
    void addNode(int node); // добавить вершину
    void addEdge(int node1, int node2);
    void DFS(int node, bool visited[]);
    void DFS(int node);
};


Graph::Graph() {

}

void Graph::addNode(int node) { // функция добавления вершины
    Node n(node);
    nodes.push_back(n);
}

void Graph::addEdge(int node1, int node2) {
    nodes[node1].edges.push_back(node2);
    nodes[node2].edges.push_back(node1);
}

void Graph::DFS(int node, bool visited[]) {
    visited[node] = true;
    cout << node << " ";
    vector<int>::iterator i;
    for (i = nodes[node].edges.begin(); i != nodes[node].edges.end(); ++i)
        if (!visited[*i])
            DFS(*i, visited);
}


void Graph::DFS(int node) {
    bool *visited = new bool[nodes.size()];
    for (int i = 0; i < nodes.size(); i++)
        visited[i] = false;
    DFS(node, visited);
}


int main() {
    Graph g;
    g.addNode(0); // добавляем вершины
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 4);
    cout << "DFS traversal starting from vertex 0: ";
    g.DFS(0);
    return 0;
}
