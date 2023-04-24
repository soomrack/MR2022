#include <iostream>

using namespace std;


class List_exceptions: public std::domain_error {
public:
    List_exceptions (const char* const error) : std::domain_error(error) {
    }
};


class Node {

public:
    Node *pnext;
    double value;
    Node();
    Node(double value = double(), Node *pnext = nullptr);
};


typedef Node *Nodeptr;


Node::Node(double value, Node *pnext) {
    this->value = value;
    this->pnext = pnext;
}


class List {
public:
    List();
    ~List();
    void push_back(double value);
    void push_front(double value);
    void push_next(double value, double value_next);
    void push_previous(double value, double value_prev);
    void delete_head();
    void clean();
    void print();

private:
    Nodeptr head;
    Nodeptr previous(double value);
};


List::List() {
    head = nullptr;
}


List::~List() {
    clean();
}


void List::push_back(double value) {
    if (head == nullptr) {
        head = new Node (value);
        return;
    }
    Node *current = head;
    while (current->pnext != nullptr){
        current = current->pnext;
    }
    current->pnext = new Node(value);
}


void List::push_front(double value) {
    head = new Node (value, head);
}


void List::push_next(double value, double value_next) {
    Nodeptr node_pr = head;
    while (node_pr->value != value_next) {
        node_pr = node_pr->pnext;
    }
    Nodeptr new_node = new Node(value, node_pr->pnext);
    node_pr->pnext = new_node;
}


void List::push_previous(double value, double value_prev) {
    Nodeptr pr = previous(value_prev);
    Nodeptr new_node = new Node(value, pr->pnext);
    pr->pnext = new_node;
}


void List::delete_head() {
    Node *current = head;
    head = head->pnext;
    delete current;
}


void List::clean() {
    while (head != nullptr) {
        delete_head();
    }
}


void List::print() {
    Node *current = head;
    while (current != nullptr) {
        cout << current->value << endl;
        current = current->pnext;
    }
}


Nodeptr List::previous(double pr_value) {
    Node *current = head;
    while (current->pnext->value != pr_value) {
        current = current->pnext;
    }
    return current;
}


int main() {
    List List;
    for (unsigned int i = 0; i < 4; i++) {
        List.push_back(rand()%10);
    }
    List.print();
    List.push_front(1);
    List.push_back(3);
    List.push_next(1, 8);
    List.push_previous(1, 8);
    List.print();
    List.clean();
    List.print();
}