#include "../List/List.h"

struct Head {
    int data;
};

struct Edge {
    Node *loc, *dest;
};

class Graph {
    List edgelist;

    addNode(int data);

    deleteNode(int *data);

    addEdge(Head *head,Edge *loc,Edge *dest);

    deleteEdge(Edge *loc,Edge *dest);

    findNode(int *data);
};

int Graph::addNode(int data) {
    Head *newNode = new Head;

}

}


int main() {

}