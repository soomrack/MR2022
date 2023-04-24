#include <iostream>
class ListExceptions{
    int kod_mistake;
public:
    ListExceptions();
    ListExceptions(int );

};


ListExceptions::ListExceptions() {
    kod_mistake = 666;
}


ListExceptions::ListExceptions(int kod_mistake) {
    this->kod_mistake = kod_mistake;
}

ListExceptions mistake_parameters = (0);


class Node {
public:
    Node* next;
    double data;
    Node();
    Node (double data = double(),Node *pNext = nullptr);
    void push_next (double data);
    void del_next (double data);
    Node* peek();

};

typedef Node *NodePtr;



class LinkedList{
private:
    Node *head;
    NodePtr previous (double data);
public:
    LinkedList();
    ~LinkedList();

    void push_back(double data);
    void del (double data);

    void push_head(double data);
    void del_head();
    NodePtr peek_head();

    void clear();
    void print();

    void push_next (double data, double data_next);
    void push_prev (double data, double data_prev);
};


Node:: Node (double data ,Node *pNext){
    this->data = data;
    this->next = pNext;
}


void Node::push_next(double data) {
    NodePtr node = next;
    NodePtr new_node = new Node (data);
    node->next = new_node;
}


void Node::del_next(double data) {
    next = next->next;
}


Node* Node:: peek(){
    return next;
}


LinkedList:: LinkedList(){
    head = nullptr;
}


LinkedList:: ~LinkedList(){
    clear();
}

NodePtr LinkedList:: peek_head(){
    return head;
}

void LinkedList::push_back(double key){
    if ( head == nullptr){
        head = new Node (key);
        return;
    }
    Node *current = head;
    while ( current->next != nullptr){
        current = current->next;
    }
    current->next = new Node (key);
}


void LinkedList::push_head(double key){
    head = new Node (key, head);
}


void LinkedList:: push_next (double data, double data_){
    NodePtr node_prev = head;
    while (node_prev->data != data_ ){
        node_prev = node_prev->next;
    }
    NodePtr new_node = new Node (data, node_prev->next);
    node_prev->next = new_node;
}


void LinkedList::push_prev(double data, double data_prev) {
    NodePtr prev = previous(data_prev);
    NodePtr new_node = new Node (data, prev->next);
    prev->next = new_node;
}


void LinkedList:: del_head(){
    Node *current = head;
    head = head->next;
    delete current;
}


void LinkedList:: clear(){
    while (head != nullptr){
        del_head();
    }
}


void LinkedList:: del(double key){
    Node* node_to_del = head;
    while ( node_to_del->data != key)
        node_to_del = node_to_del->next;
    Node *current;
    current = previous(key);
    node_to_del = current->next;
    current->next = node_to_del->next;
    delete node_to_del;
}


void LinkedList::print(){
    Node *current = head;
    while (current != nullptr){
        std::cout << current->data << "  ";
        current = current->next;
    }
    std::cout << "\n";
}


NodePtr LinkedList::previous(double data_){
    Node *current = head;
    while ( current->next->data != data_)
        current = current->next;
    return current;
}


int main() {
    LinkedList lst;
    for (int i = 0; i < 9; i++){
        lst.push_back(rand() %20);
    }
    lst.print();

    lst.push_head(8.00);
    lst.push_back(55.00);
    lst.print();
    lst.del( 1);
    lst.push_prev(666.00, 0);
    lst.push_next(999.00, 0);

    lst.print();
    lst.clear();
    lst.print();

    return 0;
}
