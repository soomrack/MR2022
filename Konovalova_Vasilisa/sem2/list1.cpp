#include <iostream>
using namespace std;

typedef int Data;

class Node {
public:
    Data data;
private:
    Node* next;
    friend class List;
public:
    Node() = delete;
    Node(const Data data, const Node* next = nullptr);
public:
    Node *get_next() { return next; }
    void add_next(Node *new_next) { next = new_next; }
    void delete_next();
};
Node::Node(const Data data, const Node* next) {
    this->data = data;
    this->next = const_cast<Node*>(next);
}
class List {

private:
    Node* head;
public:
    List() {head = nullptr;}
    ~List() {clear();}
public:
    void add_head(const Data value);
    void delete_head();
    Node* get_head(){return head;};
    void clear();
    //void add_next(Node* node, const Data value);
    //void delete_next(Node* node);

};

void Node::delete_next() {
    Node *temp = next;
    if (temp->next == nullptr) {
        next = nullptr;
    } else {
        Node *temp2 = temp->next;
        next = temp2;
    }
    delete temp;
}

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

void List::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head= nullptr;
}

int main() {
    List list;
    list.add_head(5);
    list.add_head(22);
    list.add_head(8);
    list.delete_head();
    list.clear();
    return 0;
}
