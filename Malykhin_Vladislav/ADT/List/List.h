// можно работать через узлы (push_next()/next())
// или через итераторы для двух связного списка
// tail хранить не нужно
// нельзя делать доступ по индексу
#ifndef LIST_H
#define LIST_H


#include <iostream>

class List {

public:
    class Node{ // класс узел, для добавления и удаления будем менять его поля в супер классе.
    public:
        double data;
        Node *next_ptr;
        explicit Node(double new_data);
        ~Node();
        Node &operator= (Node* other);
        Node &operator== (Node* &&other);
    };
    Node *head;
    List();
    class Iterator{
    public:
        Node *node_ptr;
        explicit Iterator();
        Iterator(Node *in_node);
        Iterator &operator++ ();
        Iterator &operator= (Node* other);
        Iterator &operator= (Iterator other);
        bool operator== (Node* &&other) const;
        bool operator!= (Node* &&other) const;
    };


    bool is_empty() ;
    unsigned int size();
    void push_head (double in);
    void pop_head ();
    void push (double in, Iterator in_itr);
    void pop (Iterator in_itr);
    void print();
};

List::Node::Node(double new_data) {
    data = new_data;
    next_ptr = nullptr;
}


List::Node::~Node(){
    data = 0;
    next_ptr = nullptr;
}


List::Node& List::Node::operator= (Node* const other){
    if(this == other) return *this;
    data = other->data;
    next_ptr = other->next_ptr;
    return *this;
}


List::Node& List::Node::operator== (Node* &&other){
    if(this == other) {
        other->data = 0;
        other->next_ptr = nullptr;
        return *this;
    }
    data = other->data;
    next_ptr = other->next_ptr;
    other->data = 0;
    other->next_ptr = nullptr;
    return *this;
}


List::Iterator::Iterator() {
    node_ptr = nullptr;
}


List::Iterator::Iterator(Node *in_node) {
    node_ptr = in_node;
}


List::Iterator& List::Iterator::operator++ () {
    if (node_ptr == nullptr) return *this;
    node_ptr = node_ptr->next_ptr;
    return *this;
}


List::Iterator& List::Iterator::operator= (Node* const other) {
    if (node_ptr == other) return *this;
    node_ptr = other;
    return *this;
}


List::Iterator& List::Iterator::operator= (Iterator const other) {
    if (node_ptr == other.node_ptr) return *this;
    node_ptr = other.node_ptr;
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
}


bool List::is_empty() {
    if (head == nullptr) return true;
    return false;
}


unsigned int List::size(){
    if (is_empty()) return 0;
    Iterator iter = head->next_ptr;
    unsigned int counter = 1;
    while(iter != nullptr){
        counter++;
        iter = iter.node_ptr->next_ptr;
    }
    return counter;
}


void List::push_head (double in) {
    Node *new_node = new Node(in);
    if (is_empty()){
        head = new_node;
        return;
    }
    new_node->next_ptr = head;
    head = new_node;
}


void List::pop_head () {
    if (is_empty()) return;
    Node *buffer_ptr = head;
    head = head->next_ptr;
    delete buffer_ptr;
}



void List:: push (double in, Iterator in_itr) {
    if (is_empty()) {
        push_head(in);
        return;
    }
    Node *new_node = new Node(in);
    new_node->next_ptr = in_itr.node_ptr->next_ptr;
    in_itr.node_ptr->next_ptr = new_node;
}


void List:: pop (Iterator in_itr) {
if (is_empty()) {
return;
}
Iterator buffer_itr;
for (buffer_itr = head; buffer_itr.node_ptr->next_ptr != in_itr.node_ptr; ++buffer_itr);
buffer_itr.node_ptr->next_ptr = in_itr.node_ptr->next_ptr;
delete in_itr.node_ptr;
} // удаление произвольного


void List:: print(){
    if (is_empty()) return;
    for(Iterator iter = head; iter.node_ptr != nullptr; ++iter)
        std::cout<<iter.node_ptr->data<<' ';
    std::cout<<"\n";
}


#endif //LIST_H