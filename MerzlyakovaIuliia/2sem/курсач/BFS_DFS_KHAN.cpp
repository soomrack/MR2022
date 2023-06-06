#include <iostream>
#include <list>
#include <stack>
#include <queue>

using namespace std;

class Graph {
    int numVertices;
    list<int>* adjLists;
    bool* visited;

public:
    Graph(int vertices);
    void addEdge(int src, int dest);
    void DFS(int vertex);
    void BFS(int startVertex);
    void topologicalSort();
};

// Initialize graph
Graph::Graph(int vertices) {
    numVertices = vertices;
    adjLists = new list<int>[vertices];
}

// Add edges
void Graph::addEdge(int src, int dest) {
    adjLists[src].push_back(dest);
}

// Depth-first search
void Graph::DFS(int vertex) {
    visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    stack<int> Stack;
    Stack.push(vertex);

    while (!Stack.empty()) {
        vertex = Stack.top();
        Stack.pop();

        if (!visited[vertex]) {
            cout << vertex << " ";
            visited[vertex] = true;
        }

        for (auto i = adjLists[vertex].begin(); i != adjLists[vertex].end(); ++i)
            if (!visited[*i])
                Stack.push(*i);
    }
}

// Breadth-first search
void Graph::BFS(int startVertex) {
    visited = new bool[numVertices];
    for(int i = 0; i < numVertices; i++)
        visited[i] = false;

    list<int> queue;

    visited[startVertex] = true;
    queue.push_back(startVertex);

    list<int>::iterator i;

    while(!queue.empty()) {
        startVertex = queue.front();
        cout << startVertex << " ";
        queue.pop_front();

        for (i = adjLists[startVertex].begin(); i != adjLists[startVertex].end(); ++i) {
            if (!visited[*i]) {
                queue.push_back(*i);
                visited[*i] = true;
            }
        }
    }
}

// Topological sort
void Graph::topologicalSort() {
    stack<int> Stack;
    bool *visited = new bool[numVertices];
    for (int i = 0; i < numVertices; i++)
        visited[i] = false;

    for (int i = 0; i < numVertices; i++)
        if (!visited[i])
            for (auto j = adjLists[i].begin(); j != adjLists[i].end(); ++j) {
                Stack.push(*j);
                visited[*j] = true;
            }

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}
