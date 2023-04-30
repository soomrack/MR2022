#include <iostream>
#include <string>

template<typename T>
class Node {
public:
    Node<T>* next;
    Node(T _val) : val(_val), next(nullptr) {}
    T val;
};

template<typename T>
class Stack {
public:
    Node<T>* sp;
    Node<T>* last;

    Stack() : sp(nullptr), last(nullptr) {}
    bool is_empty() ;
    void push(T _val);
    void print();
    void pop() ;
};


template<typename T>
bool Stack<T>::is_empty() {
    return sp == nullptr;
}

template<typename T>
void Stack<T>::push(T _val) {
    Node<T>* p = new Node(_val);
    if (is_empty()) {
        sp = p;
        last = p;
        return;
    }
    p->next = sp;
    sp = p;
}

template<typename T>
void Stack<T>::print() {
    if (is_empty()) {
        std::cout << "no values" << std::endl;
        return;
    }
    std::cout << sp->val << std::endl;
}

template<typename T>
void Stack<T>::pop() {
    if (is_empty()) return;
    Node<T>* p = sp;
    sp = p->next;
    delete p;
}


int main()
{
    Stack<unsigned int> number;
    return 0;
}
