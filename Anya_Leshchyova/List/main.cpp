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



class List{
public:
    List();
    ~List();

    void push_black(double);
    void push_front(double);
    void print();
    double& operator[] (const int );
    void del ( int );
    void del_head();
    void clear();
    void insert(double, int);
    void del_black();


private:

    class Node{
    public:
        Node *pNext;
        double data;

        Node (double data = double(),Node *pNext = nullptr){
            this->data = data;
            this->pNext = pNext;
        }
    };
    Node *head;
    int size;
    typedef Node *NodePtr;
    NodePtr previous (int);
};


List:: List(){
    size = 0;
    head = nullptr;
}


List:: ~List(){
    clear();
}


double& List::operator[](const int number) {
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


void List::push_black(double key){
    if ( head == nullptr){
        head = new Node (key);
        return;
    }
    Node *current = head;
    while ( current->pNext != nullptr){
        current = current->pNext;
    }
    current->pNext = new Node (key);
    size++;
}


void List::push_front(double key){
    head = new Node (key, head);
    size++;
}


void List::insert(double key, int place) {
    if ( place < 0) throw mistake_parameters;
    if ( place == 0){
        push_front(key);
        return;
    }
    Node *current = previous(place);
    Node *insert_node = new Node (key, current->pNext);
    current->pNext = insert_node;
    size++;
}


void List:: del_head(){
    Node *current = head;
    head = head->pNext;
    delete current;
    size--;

}


void List:: clear(){
    while (size){
        del_head();
    }
}


void List:: del(int place){
    if ( place < 0) throw mistake_parameters;
    if (place == 0){
        del_head();
        return;
    }
    Node *current;
    current = previous(place);
    Node *to_del = current->pNext;
    current->pNext = to_del->pNext;
    delete to_del;
    size--;
}


void List::del_black() {
    del(size-1);
    return;
}


void List::print(){
    Node *current = head;
    for (int i = 0; i < size; i++){
        std::cout << current->data << "  ";
        current = current->pNext;
    }
    std::cout << "\n";
}


List::NodePtr List::previous(int place) {
    Node *current = head;
    for ( int i = 0; i < place - 1; i ++){
        current = current->pNext;
    }
    return current;
}


int main() {
    List lst;
    for (int i = 0; i < 10; i++){
        lst.push_black(rand() %20);
    }
    lst.print();
    std:: cout <<lst[2] << "\n";
    lst.push_front(8.00);
    lst.push_black(444.00);
    lst.insert(888.00, 1);
    lst.print();
    lst.del( 1);
    lst.print();
    lst.del_black();
    lst.del_black();
    lst.print();
    lst.clear();
    lst.print();


    return 0;
}
