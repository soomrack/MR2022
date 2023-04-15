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
class Node{
public:
    Node *pNext;
    double data;

    Node (double data = double(),Node *pNext = nullptr);
};

Node:: Node (double data ,Node *pNext){
    this->data = data;
    this->pNext = pNext;
}


class LinkedList{
public:
    LinkedList();
    ~LinkedList();

    void push_back(double key);
    void push_front(double key);
    void print();
    double& operator[] (const int );
    void del ( int );
    void del_head();
    void clear();
    void insert(double key, int place);



private:
Node *head;
typedef Node *NodePtr;
NodePtr previous (int key);
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


void LinkedList::insert(double key, int place) {
    if ( place < 0) throw mistake_parameters;
    if ( place == 0){
        push_front(key);
        return;
    }
    Node *current = previous(place);
    Node *insert_node = new Node (key, current->pNext);
    current->pNext = insert_node;
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


void LinkedList:: del(int key){
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


LinkedList::NodePtr LinkedList::previous(int key) {
    Node *current = head;
    while ( current->pNext->data != key)
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
    lst.insert(888.00, 1);
    lst.print();
    lst.del( 1);
    lst.print();

    lst.clear();
    lst.print();


    return 0;
}
