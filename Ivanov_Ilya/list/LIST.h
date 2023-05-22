#ifndef LIST_h
#define LIST_h

#include <iostream>

class List_error : public std::runtime_error {
public:
    List_error(const std::string& message) : std::runtime_error(message) {}
};
List_error EMPTY ("LIST IS EMPTY");
class Node {
private:
    Node* next;

public:
    int data;

    Node();
    Node(const int new_data, Node* new_next): data(new_data), next(new_next) {};
    Node* get_next();
    void add_next(const int data);
    void del_next();
};

class List {
private:
    Node* head;

public:
    List();
    ~List();
    int get_head();
    void del_head();
    void add_head(const int data);
    void print();
};

Node::Node() : next(nullptr) {}

Node* Node::get_next() {
    return next;
}

List::List() : head(nullptr) {}

List::~List() {
    while (head != nullptr) {
        del_head();
    }
}

int List::get_head() {
    if (head != nullptr) {
        return head->data;
    }
    return 0;
}

void List::del_head() {
    if (head == nullptr) throw EMPTY;
        Node* node_to_delete = head;
        head = head->get_next();
        delete node_to_delete;
}

void List::add_head(const int data) {
    Node* new_head = new Node(data, head);
    head = new_head;
}
void Node::add_next(const int data) {
    Node* new_node = new Node(data, next);
    next = new_node;
}

void Node::del_next() {
    if (next == nullptr) {
        throw List_error("No next node to delete.");
    }
    Node* node_to_delete = next;
    next = next->get_next();
    delete node_to_delete;
}

void List::print() {
    Node* current_node = head;
    while (current_node != nullptr) {
        std::cout << current_node->data << " ";
        current_node = current_node->get_next();
    }
    std::cout << std::endl;
}

#endif /* LIST_h */
