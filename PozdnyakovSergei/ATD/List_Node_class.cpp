#include <iostream>

using namespace std;


class Node {
public:
    Node *pNext;
    double value;
    Node (double value = double(), Node *pNext = nullptr);
};
Node::Node(double value, Node *pNext) {
    this->value = value;
    this->pNext = pNext;
}


class List {
public:
    List();
    ~List();
    void push_front(double key);
    void push_back(double key);
    void print();
    void clean_head();
    void clean();
    void set(double key, int number);
private:
    Node *head;
    typedef Node *NodePtr;
    NodePtr previous (int key);
};


List::List() {head = nullptr;}


List::~List() {clean();}


void List::push_back(double key) {
    if (head == nullptr) {
        head = new Node(key);
        return;
    }
    Node *current = head;
    while (current->pNext != nullptr) {
        current = current->pNext;
    }
    current->pNext = new Node(key);
}


void List::push_front(double key) {
    head = new Node (key, head);
}


void List::set(double key, int number) {
    if (number = 0) {
        push_front(key);
        return;
    }
    Node *current = previous(number);
    Node *insert_node = new Node(key, current->pNext);
    current->pNext = insert_node;
}


void List::clean_head() {
    Node *current = head;
    head = head->pNext;
    delete current;
}


void List::clean() {
    while (head != nullptr) {
        clean_head();
    }
}


void List::print() {
    Node *current = head;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->pNext;
    }
    cout << endl;
}


List::NodePtr List::previous(int key) {
    Node *current = head;
    while(current->pNext->value != key) {
        current = current->pNext;
        return current;
    }
}


int main() {
    List list;
    for (int i = 0; i < 5; i++) {
        list.push_back(rand()%10);
        list.print();
        list.push_front(3);
        list.push_back(2);
        list.print();
        list.set(5, 3);
        list.print();
        list.clean();
        list.print();
        return 0;
    }
}
