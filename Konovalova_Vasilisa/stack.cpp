#include <iostream>


template<typename T>
class Node {
private:
    friend class stack;
    Node* next;
public:
    Node(T _val) : val(_val), next(nullptr) {}

    T val;
};

template<typename T>
class stack {
private:
    Node*<T> st;
    Node* last;
public:
    stack() : st(nullptr), last(nullptr) {}

    bool is_empty() ;
    void push(int _val);
    void print();
    void pop() ;
};



bool stack::is_empty() {
    return st == nullptr;
}

void stack::push(int _val) {
    Node* el = new Node(_val);
    if (is_empty()) {
        st = el;
        last = el;
        return;
    }
    el->next = st;
    st = el;

}

void stack::print() {
    if (is_empty()) {
        std::cout << "stack is empty" << std::endl;
        return;
    }
    std::cout << st->val << std::endl;
}

void stack::pop() {
    if (is_empty()) return;
    Node* el = st;
    st = el->next;
    delete el;
}


int main()
{
    stack<int> A;
    A.push(3);
    std::cout << "is emty?"<< A.is_empty() << std::endl;
    A.print();
    A.push(2);
    A.print();
    A.pop();
    A.print();
    A.pop();
    A.print();

    return 0;
}
