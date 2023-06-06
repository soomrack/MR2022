#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node
{
    int val;
    Node *next;
};

class List
{
private:
    Node *first;
    Node *last;

public:

    void push_last(int value);
    void print();
    void push_first(int value);
    void remove_first();
    void remove_last();
    void fill();
    void clean();
    List() : first(nullptr), last(nullptr) {}
};


void List::push_last(int value)
{
    Node *p = new Node;
    p->val = value;
    p->next = nullptr;

    if(first == nullptr)
    {
        first = p;
        last = p;
        p = nullptr;
    }
    else
    {
        last->next = p;
        last = p;
    }
}

void List::print(){
    Node *p = new Node;
    p = first;
    while(p != nullptr)
    {
        cout << p->val << "\t";
        p = p->next;
    }
    cout << endl;
}

void List::push_first(int value){
    Node *p = new Node;
    p->val = value;
    p->next = first;
    first = p;
}

void List::remove_first() {
    Node *p = new Node;
    p = first;
    first = first->next;
    delete p;
}

void List::remove_last()
{
    Node *current = new Node;
    Node *previous = new Node;
    current = first;
    while(current->next != nullptr)
    {
        previous = current;
        current = current->next;
    }
    last = previous;
    previous->next = NULL;
    delete current;
}


void List::fill(){
    srand(time(0));
    for (int el = 0; el < 5; el++)
    {
        push_last(rand() % 20);
    }
}

void List::clean()
{
    first = nullptr;
    last = nullptr;
}

int main()
{
    List l;

    l.fill();
    l.print();
    l.push_last(1);
    l.print();
    l.push_first(2);
    l.print();
    l.remove_first();
    l.print();
    l.remove_last();
    l.print();
    l.clean();
    return 0;
}
