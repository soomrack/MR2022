#include <iostream>
class ListExceptions{
    int kod_mistake;
public:
    ListExceptions();
    ListExceptions(int kod);

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
    Node* pNext;
    double data;
    Node();
    Node (double data = double(),Node *pNext = nullptr);
};

typedef Node *NodePtr;

Node:: Node (double data ,Node *pNext){
    this->data = data;
    this->pNext = pNext;
}


class LinkedList{
public:
    LinkedList();
    ~LinkedList();
    void push_back(double data);
    void push_front(double data);
    void print();
    double& operator[] (const int );
    void del (double data);
    void del_head();
    void clear();
    void push_next (double data, double data_next);
    void push_prev (double data, double data_prev);

private:
NodePtr head;
NodePtr previous (double data);
};


LinkedList:: LinkedList(){
    head = nullptr;
}


LinkedList:: ~LinkedList(){
    clear();
}


double& LinkedList::operator[](const int number) {
    if ( number < 0) throw mistake_parameters;
    Node *current = head;
    if (number == 0) return current->data;
    int count = 0;
    do {
        current = current->pNext;
        count++;
    }
    while(count != number);
    return current->data;
}


void LinkedList::push_back(double key){
    if ( head == nullptr){
        head = new Node (key);
        return;
    }
    Node *current = head;
    while ( current->pNext != nullptr){
        current = current->pNext;
    }
    current->pNext = new Node (key);
}


void LinkedList::push_front(double key){
    head = new Node (key, head);
}


void LinkedList:: push_next (double data, double data_){
    NodePtr node_prev = head;
    while (node_prev->data != data_ ){
        node_prev = node_prev->pNext;
    }
    NodePtr new_node = new Node (data, node_prev->pNext);
    node_prev->pNext = new_node;
}


void LinkedList::push_prev(double data, double data_prev) {
    NodePtr prev = previous(data_prev);
    NodePtr new_node = new Node (data, prev->pNext);
    prev->pNext = new_node;
}


void LinkedList:: del_head(){
    Node *current = head;
    head = head->pNext;
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
        node_to_del = node_to_del->pNext;
    Node *current;
    current = previous(key);
    node_to_del = current->pNext;
    current->pNext = node_to_del->pNext;
    delete node_to_del;
}


void LinkedList::print(){
    Node *current = head;
    while (current != nullptr){
        std::cout << current->data << "  ";
        current = current->pNext;
    }
    std::cout << "\n";
}


NodePtr LinkedList::previous(double data_){
    Node *current = head;
    while ( current->pNext->data != data_)
        current = current->pNext;
    return current;
}


int main() {
    LinkedList lst;
    for (int i = 0; i < 9; i++){
        lst.push_back(rand() %20);
    }
    lst.print();
    std:: cout <<lst[2] << "\n";
    lst.push_front(8.00);
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
