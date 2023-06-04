#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 
#include <iostream>

struct node
{
    int data;
    node* next;
};

class Linked_list {
private:
    unsigned int size;
    node* head, *tail;
public:
    Linked_list();
    ~Linked_list();
    void push(int x);
    int pop();
    void print();
};

Linked_list::Linked_list() {
    head = nullptr;
    tail = nullptr;
    size = NULL;
}

Linked_list::~Linked_list() {
    node* tmp = new node;
    node* i = head;

    while (i != nullptr) {
        node* tmp = i->next;
        delete i;
        i = tmp;
    }

    head = nullptr;
    size = NULL;
    free(i);
    
}

void Linked_list::push(int x) {
    node* tmp = new node;
    tmp->data = x;
    tmp->next = nullptr;

    if (head == nullptr)
    {
        head = tmp;
        tail = tmp;
    }
    else
    {
        tail->next = tmp;
        tail = tail->next;
    }
}

int Linked_list::pop() {
node * tmp = head;
int ret = tmp->data;
head = head->next;
return ret;
}

void Linked_list::print() {
    node* tmp = head;
    while (tmp != nullptr) {
        
        std::cout << tmp->data << std::endl;
        tmp = tmp->next;
    }
    
}

void main() {
    Linked_list list;
    list.push(10);
    list.push(10);
    list.push(10);
    list.push(10);
    list.pop();
    list.pop();
    list.pop();
    list.print();
}