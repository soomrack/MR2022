#include <iostream>


class Node {
private:
    friend class queue;
    int val;
    Node* next;
public:
    Node(int _val) : val(_val), next(nullptr) {}
};

class queue {
private:
    Node* first;
    Node* last;
public:
    queue() : first(nullptr), last(nullptr) {}

    bool is_empty() ;

    void push_back(int _val);

    void print();

    Node* find(int _val) ;

    void remove_first() ;

};



bool queue::is_empty() {
    return first == nullptr;
}

void queue::push_back(int _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        first = p;
        last = p;
        return;
    }
    last->next = p;
    last = p;

}

void queue::print() {
    if (is_empty()) return;
    Node* p = first;
    while (p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

Node* queue::find(int _val) {
    Node* p =first;
    while (p && p->val != _val)  p->next;
    return (p && p->val == _val) ? p : nullptr;
}

void queue::remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}


int main()
{
    queue l;
    std::cout << l.is_empty() << std::endl;
    l.push_back(3);
    l.push_back(123);
    l.push_back(8);
    l.print();
    std::cout << l.is_empty() << std::endl;
    l.push_back(1234);
    l.remove_first();
    l.print();
    return 0;
}
