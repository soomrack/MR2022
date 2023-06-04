#include <iostream>


struct Node {
    int val;
    Node* next;
    Node(int _val) : val(_val), next(nullptr) {}
};

struct list {
    Node* first;
    Node* last;

    list() : first(nullptr), last(nullptr) {}

    bool is_empty() ;

    void push_back(int _val);

    void print();

    Node* find(int _val) ;

    void remove_first() ;

    void remove_last();
    void remove(int _val);
    Node* operator[] (const int index);
};



bool list::is_empty() {
    return first == nullptr;
}

void list::push_back(int _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        list::first = p;
        list::last = p;
        return;
    }
    list::last->next = p;
    list::last = p;

}

void list::print() {
    if (is_empty()) return;
    Node* p = first;
    while (p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

Node* list::find(int _val) {
    Node* p =first;
    while (p && p->val != _val)  p->next;
    return (p && p->val == _val) ? p : nullptr;
}

void list::remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}

void list::remove_last() {
    if (is_empty()) return;
    if (first == last) {
        remove_first();
        return;
    }
    Node* p = first;
    while (p->next != last)  p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
}
void list::remove(int _val) {
    if (is_empty()) return;
    if (first->val == _val) {
        remove_first();
        return;
    }
    else if (last->val == _val) {
        remove_last();
        return;
    }
    Node* p = first;
    Node* r = first->next;
    while (r && r->val != _val) {
        r = r->next;
        p = p->next;
    }
    if (!r) return;
    p->next = r->next;
    delete r;
}

Node* list::operator[](const int index) {
    if (is_empty()) return nullptr;
    Node* p = first;
    for ( int count = 0; count < index; count++) {
        p = p->next;
        if (!p) return nullptr;
    }
    return p;
}


int main()
{
    list l;
    std::cout << l.is_empty() << std::endl;
    l.push_back(3);
    l.push_back(123);
    l.push_back(8);
    l.print();
    std::cout << l.is_empty() << std::endl;
    l.remove(123);
    l.print();
    l.push_back(1234);
    l.remove_first();
    l.print();
    l.remove_last();
    l.print();
    std::cout << l[0]->val << std::endl;
    return 0;
}
