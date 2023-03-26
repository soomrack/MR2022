#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;


struct Node {
    int data;
    Node *pNext;
};

class List {
private:
    Node *head;
    Node *tail;
public:
    List();
//    ~List();
    void push_head (int value);
    void push_tail (int value);
    void delete_head ();
    void delete_tail ();
//    void delete_pos (int pos);
    void fill_random (int total);
    void clean ();
    void print ();
};


class List_Exceptions: public std::domain_error {
public:
    List_Exceptions(const char* const error) : std::domain_error(error){}
};


List_Exceptions IS_EMPTY ("Error: List is empty");


List::List() {
    head = nullptr;
    tail = nullptr;
}


void List::push_head(int value) {
    cout << "Adding to the head" << "\n";
    Node *temp = new Node;
    temp -> data = value;
    temp -> pNext = head;
    head = temp;
}


void List::push_tail(int value) {
    cout << "Adding to the tail" << "\n";
    Node *temp = new Node;
    temp->data = value;
    temp->pNext = nullptr;

    if (head == nullptr) {
        head = temp;
        tail = temp;
        temp = nullptr;
    }
    else {
        tail->pNext = temp;
        tail = temp;
    }
}


void List::delete_head() {
    if (head == nullptr && tail == nullptr) {
        throw IS_EMPTY;
    }
    cout << "Delete head" << "\n";
    Node *temp = new Node;
    temp = head;
    head = head->pNext;
    delete temp;
}


void List::delete_tail() {
    if (head == nullptr && tail == nullptr) {
        throw IS_EMPTY;
    }
    cout << "Delete tail" << "\n";
    Node *current = new Node;
    Node *prev = new Node;
    current = head;
    while (current->pNext != nullptr) {
        prev = current;
        current = current->pNext;
    }
    tail = prev;
    prev->pNext = NULL;
    delete current;
}


/*void List::delete_pos(int position) {
    Node *current = new Node;
    Node *prev = new Node;
    current = head;
    for (int i = 0; i < position; ++i) {
        prev = current;
        current = current->pNext;
    }
    prev->pNext = current->pNext;
}*/


void List::fill_random(int total) {
    srand(time(NULL));
    cout << "Fill random" << "\n";
    for (unsigned int item = 0; item < total; item++) {
        push_tail(rand() % 100);
    }
}


void List::clean() {
    head = nullptr;
    tail = nullptr;
}


void List::print() {
    Node *temp = new Node;
    temp = head;
    while (temp != nullptr) {
        cout << temp -> data << "\t";
        temp = temp->pNext;
    }
    cout << "\n";
}


int main () {
    List L;

    L.fill_random(5);
    L.print();

    L.push_head(10);
    L.print();

    L.push_tail(10);
    L.print();

    L.delete_head();
    L.delete_tail();
    L.print();

//    L.delete_pos(4);
    L.clean();
}









