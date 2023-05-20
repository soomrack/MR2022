#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
    Node* next;
    Node() = delete;
    Node(const Data data, const Node* next = nullptr);
};

Node::Node(const Data data, const Node* next) {
    this->data = data;
    this->next = const_cast<Node*>(next);
}

class List {
private:
    Node* head;
public:
    List() {
        head = nullptr;
    }

    ~List() {
        clear();
    }

public:
    void add_head(const Data value);
    void delete_head();
    Node* get_head();
    void clear();
    void add_next(Node* node, const Data value);
    void delete_next(Node* node);
};

void List::add_head(const Data value) {
    head = new Node(value, head);
}

void List::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

Node* List::get_head() {
    return head;
}

void List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void List::add_next(Node* node, const Data value) {
    if (node == nullptr) {
        return;
    }

    node->next = new Node(value, node->next);
}

void List::delete_next(Node* node) {
    if (node == nullptr || node->next == nullptr) {
        return;
    }

    Node* temp = node->next;
    node->next = temp->next;
    delete temp;
}

int main() {
    List list;
    list.add_head(5);
    list.add_head(22);
    list.add_head(8);
    list.delete_next(list.get_head());
    list.clear();
    return 0;
}
