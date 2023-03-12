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
    Node*<T> sp;
    Node* last;
public:
    stack() : sp(nullptr), last(nullptr) {}

    bool is_empty() ;
    void push(int _val);
    void print_sp_val();
    Node* find(int _val) ;
    void pop() ;
};



bool stack::is_empty() {
    return sp == nullptr;
}

void stack::push(int _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        sp = p;
        last = p;
        return;
    }
    p->next = sp;
    sp = p;

}

void stack::print_sp_val() {
    if (is_empty()) {
        std::cout << "no values" << std::endl;
        return;
    }
    std::cout << sp->val << std::endl;
}

void stack::pop() {
    if (is_empty()) return;
    Node* p = sp;
    sp = p->next;
    delete p;
}


int main()
{
    stack<int> l;
    std::cout << "is emty?"<< l.is_empty()<< std::endl;
    l.push(3);
    std::cout << "is emty?"<< l.is_empty() << std::endl;
    l.print_sp_val();
    l.push(123);
    l.print_sp_val();
    l.pop();
    l.print_sp_val();
    l.pop();
    l.print_sp_val();

    return 0;
}
