
#include <iostream>

using namespace std;

struct Node {  // Структура данных для хранения узлов списка смежности
    int id;
    Node *next;
};

struct Edge {  // Структура данных для хранения ребра Graph
    int loc, dest;
};

class Graph {
    Node *getAdjListNode(int dest, Node *head) {  // Функция связи узлов рёбрами
        Node *newNode = new Node;
        newNode->id = dest;
        newNode->next = head; // указываем новый узел на текущую голову
        return newNode;
    }

    int NodeNum;  // общее количество узлов в Graph

public:
    Node **head;  // Массив указателей на Node для представления списка смежности

    Graph(Edge edgeslist[], int edges, int Nodes) {  // Конструктор
        head = new Node *[Nodes]();  // выделить память
        this->NodeNum = Nodes;
        for (int i = 0; i < Nodes; i++) {  // инициализируем головной указатель для всех вершин
            head[i] = nullptr;
        }
        for (unsigned i = 0; i < edges; i++) {  // добавляем ребра в ориентированный graph
            Node *newNode = getAdjListNode(edgeslist[i].dest, head[edgeslist[i].loc]);  // соединение узлов c рёбрами
            head[edgeslist[i].loc] = newNode;  // головной указатель теперь на данном узле
        }
    }

    ~Graph() {  // Деструктор
        for (int i = 0; i < NodeNum; i++) {
            delete[] head[i];
        }
        delete[] head;
    }
};

void printList(Node *ptr) {  // Функция для печати всех соседних вершин данной вершины
    while (ptr != nullptr) {
        cout << " >> " << ptr->id;
        ptr = ptr->next;
    }
    cout << endl;
}

int main() {
    // массив ребер Graph согласно схеме выше
    Edge edges[] =
            {
                    // пара {x, y} представляет ребро от `x` до `y`
                    {0, 1},
                    {1, 2},
                    {2, 0},
                    {2, 1},
                    {3, 2},
                    {4, 5},
                    {5, 4}
            };

    // общее количество узлов в Graph
    int N = 6;

    // вычисляем общее количество ребер
    int n = sizeof(edges) / sizeof(edges[0]);

    // построить Graph
    Graph graph(edges, n, N);

    // вывести представление списка смежности Graph
    for (int i = 0; i < N; i++) {
        cout << i;
        printList(graph.head[i]);
    }

    return 0;
}
