#include <iostream>

using namespace std;


class List_exceptions: public std::domain_error {
public:
    List_exceptions (const char* const error) : std::domain_error(error) {
    }
};


class Node {
private:
    Node *pnext;
public:
    double value;
    Node();
    Node(double values = double(), Node *pnext = nullptr);

    Node *get_next() {return pnext;}
    void push_next(double value);
    void del_next();
    void set_next(Node *new_next) {pnext = new_next;}
};


void Node::push_next(double value) {
    Node *temp = new Node(value);
    if (pnext == nullptr) {
        pnext = temp;
    }
    else {
        Node *temp2 = pnext;
        temp->pnext = temp2;
        pnext = temp;
    }
}


void Node::del_next() {
    if (pnext = nullptr) {}
    Node *temp = pnext;
    if (temp->pnext == nullptr) {
        pnext = nullptr;
    }
    else {
        Node *temp2 = temp->pnext;
        pnext = temp2;
    }
    delete temp;
}


typedef Node *Nodeptr;


Node::Node(double value, Node *pnext) {
    this->value = value;
    this->pnext = pnext;
}


class List {
public:
    List();
    ~List();

    Node *head;

    void push_head(double value);
    Node *del_head();
    Node *get_head();

    void push_back(double value);
    void push_front(double value);

    void push_next(double value, unsigned int index);
    //void push_previous(double value, double value_prev);
    void del_next(unsigned int index);
    //void delete_head();
    void clean();
    void print();

private:
//    Nodeptr previous(double value);
};


List::List() {
    head = nullptr;
}


List::~List() {
    clean();
}


void List::push_head(double value) {
    Node *temp = new Node(value);
    if (head == nullptr) {
        head = temp;
    }
    else {
        temp->set_next(head);
        head = temp;
    }
}


Node *List::del_head() {
    Node *temp = head;
    if (head->get_next() == nullptr) {
        head = nullptr;
    }
    else {
        head = head->get_next();
    }
    return temp;
}


void List::clean() {
    while (head != nullptr) {
        Node *temp = head;
        head = head->get_next();
        delete temp;
    }
}


void List::push_next(double value, unsigned int index) {
    Node *temp = head;
    for (int count = 0; count < index; count++) {
        temp = temp->get_next();
    }
    temp->push_next(value);
}


void List::del_next(unsigned int index) {
    Node *temp = head;
    for (unsigned int count = 0; count < index; count++) {
        temp = temp->get_next();
    }
    temp->del_next();
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
 //   List.push_previous(1, 8);
    List.print();
    List.clean();
    List.print();
}