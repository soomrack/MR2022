#include <iostream>
using namespace std;

class Graph {
private:
  //  Структура для описания списка смежности
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node** adj_list;
    int num_vertices;

public:
  Graph(int n);
  ~Graph();
  void add_vertex(int v);  //  Метод для добавления вершины
  void add_edge(int v1, int v2);  //  Метод для добавления пути
  void del_edge(int v1, int v2);  //  Метод для удаления пути
};
  
  
    Graph::Graph(int n) : num_vertices(n) {
        adj_list = new Node*[num_vertices];
        for (int i = 0; i < num_vertices; ++i) {
            adj_list[i] = nullptr;
        }
    }

    Graph::~Graph() {
        for (int i = 0; i < num_vertices; ++i) {
            Node* current = adj_list[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }
        delete[] adj_list;
    }

    void Graph::add_vertex(int v) {
        adj_list[v] = new Node(v);
    }

    void Graph::add_edge(int v1, int v2) {
        Node* new_edge = new Node(v2);
        new_edge->next = adj_list[v1];
        adj_list[v1] = new_edge;

        new_edge = new Node(v1);
        new_edge->next = adj_list[v2];
        adj_list[v2] = new_edge;
    }

    void Graph::del_edge(int v1, int v2) {
        Node* current = adj_list[v1];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->data == v2) {
                if (prev == nullptr) {
                    adj_list[v1] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }

        current = adj_list[v2];
        prev = nullptr;

        while (current != nullptr) {
            if (current->data == v1) {
                if (prev == nullptr) {
                    adj_list[v2] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }


int main() {
    Graph g(5);

    g.add_vertex(0);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_vertex(4);

    g.add_edge(0, 1);
    g.add_edge(0, 4);
    g.add_edge(1, 2);
    g.add_edge(1, 3);
    g.add_edge(1, 4);
    g.add_edge(2, 3);
    g.add_edge(3, 4);

    g.del_edge(0, 4);
    g.del_edge(1, 4);

    return 0;
}
