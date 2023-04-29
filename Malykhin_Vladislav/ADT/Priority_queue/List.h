#ifndef LIST_H
#define LIST_H


#include <iostream>

class List {
public:
    class Node{ // класс узел, для добавления и удаления будем менять его поля в супер классе.
    public:
        int priority;
        double data;
        Node *next;
        explicit Node(double new_data, int new_prio);
        ~Node();
    };

    List();
    class Iterator{
    public:
        Node *node_ptr;
        explicit Iterator();
        Iterator(Node *in_node);
        Iterator &operator++ ();
        bool operator== (Node* &&other) const;
        bool operator!= (Node* &&other) const;
    };


    bool is_empty() ;
    unsigned int size();
    void push (double in, int new_prio);
    void pop_tail ();
    Node get_tail();
    Node get_head();

private:
    Node *head;
    Node *tail;
};

List::Node::Node(double new_data, int new_prio) {
    priority = new_prio;
    data = new_data;
    next = nullptr;
}


List::Node::~Node(){
    priority = 0;
    data = 0;
    next = nullptr;
}



List::Iterator::Iterator() {
    node_ptr = nullptr;
}


List::Iterator::Iterator(Node *in_node) {
    node_ptr = in_node;
}


List::Iterator& List::Iterator::operator++ () {
    if (node_ptr == nullptr) return *this;
    node_ptr = node_ptr->next;
    return *this;
}


bool List::Iterator::operator== (Node* &&other) const {
    if (node_ptr == other) return true;
    return false;
}



bool List::Iterator::operator!= (Node* &&other) const {
    if (node_ptr != other) return true;
    return false;
}


List::List(){
    head = nullptr;
    tail = nullptr;
}


bool List::is_empty() {
    if (head == nullptr) return true;
    return false;
}


unsigned int List::size(){
    if (is_empty()) return 0;
    Iterator iter = head->next;
    unsigned int counter = 1;
    while(iter != nullptr){
        counter++;
        iter = iter.node_ptr->next;
    }
    return counter;
}


void List::push (double in, int new_prio) {
    Node *new_node = new Node(in, new_prio);
    if (is_empty()){
        head = new_node;
        tail = new_node;
        return;
    }
    if(head->priority < new_prio)
    {
        new_node->next = head;
        head = new_node;
        return;
    }
    Node *iter = head; // для остальных списков
    while(iter->next->priority < new_prio || iter->next != nullptr)
        iter = iter->next;
    new_node->next = iter->next;
    iter->next = new_node;
}

void List::pop_tail() {
    if(is_empty()) return; // для пустого списка
    if(size() == 1) { // для списка из одного элемента
    delete head;
    head = nullptr;
    tail = nullptr;
    return;
    }
    Node *iter = head; // для остальных списков
    for(unsigned int new_size = 1; new_size < size() - 1; new_size++) { // возможен баг, при возникновении < заменить на <=
    iter = iter->next;
    }
    delete tail;
    tail = iter;
    tail->next = nullptr;
}

List::Node List::get_head() {
    return *head;
}

List::Node List::get_tail() {
    return *tail;
}

#endif //LIST_H
