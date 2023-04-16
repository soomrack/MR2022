#include <iostream>

using namespace std;


class Node {
public:
    Node *pNext;
    double value;
    Node(double value = double (), Node *pNext = nullptr);
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
    double& operator[] (const int num);
    void del(int );
    void clean();
    void delete_head();
    void insert_item(double key, unsigned int number);
    void print();
private:
    Node *head;
    typedef Node *NodePtr;
    NodePtr previous(int key);
};


List::List() {
    head = nullptr;
}


List::~List() {
    clean();
}


void List::push_front(double key) {
    head = new Node (key, head);
}


void List::push_back(double key) {
    if (head == nullptr) {
        head = new Node(key);
        return;
    }
    Node *current = head;
    while (current->pNext != nullptr) {
        current->pNext = new Node(key);
    }
    current->pNext = new Node(key);
}

double &List::operator[](const int num) {
    Node *current = head;
    if (num == 0) {
        return current->value;
    }
    int counter = 0;
    do {
        current = current->pNext;
        counter++;
    } while (counter != num);
    return current->value;
}


void List::insert_item(double key, unsigned int number) {
    if (number == 0) {
        push_front(key);
        return;
    }
    Node *current = previous(number);
    Node *insert_Node = new Node (key, current->pNext);
    current->pNext = insert_Node;
}


void List::clean() {
    while (head != nullptr) {
        delete_head();
    }
}


void List::delete_head() {
    Node *current = head;
    head = head->pNext;
    delete current;
}


void List::del(int key) {
    Node* node_del = head;
    while (node_del->value != key) {
        node_del = node_del->pNext;
    }
    Node *current;
    current = previous(key);
    node_del = current->pNext;
    current->pNext = node_del->pNext;
    delete node_del;
}


List::NodePtr List::previous(int key) {
    Node *current = head;
    while (current->pNext->value != key) {
        current = current->pNext;
    }
    return current;
}


void List::print() {
    Node *current = head;
    while (current != nullptr) {
        cout << current->value << ' ';
        current = current->pNext;
    }
    cout << endl;
}


int main() {
    List List;
    for (unsigned int num = 0; num < 5; ++num) {
        List.push_back(rand()%100);
    }
    List.print();
    List.push_front(2);
    List.push_front(9);
    List.push_front(3);
    List.push_front(5);
    List.print();
    cout << List[3] << endl;
    List.del(3);
    List.print();
    List.clean();
    List.print();
    return 0;
}