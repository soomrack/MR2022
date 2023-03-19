#include <iostream>


//template <typename T>
class Node {
private:
    friend class tree;
    int val;
    Node* left;
    Node* right;
public:
    Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

//template <typename T>
class tree {
private:
    Node* first;
public:
    tree() : first(nullptr) {}

    bool is_empty() ;

    void push(int _val);

    void print();

    Node* find(int _val) ;

    void remove_first() ;

    void remove_last();
    void remove(int _val);
    Node* operator[] (const int index);
};

bool tree::is_empty() {
    return first == nullptr;
}

void tree::push(int _val) {
    Node* p = new Node(_val);
    if (is_empty()) {
        first = p;
        return;
    }
    Node* r = first;
    bool exit = true;
    while (exit) {
        if (_val > r->val) {
            if (r->right) {
                r = r->right;
            }
            else {
                r->right = p;
                exit = false;
            }
        }
        if (_val < r->val) {
            if (r->left) {
                r = r->left;
            }
            else {
                r->left  = p;
                exit = true;
            }
        }
    }
}

void tree::print() {
    if (is_empty()) return;
    Node* r = first;
    Node* l = first;
    bool exit = false;
    while (!exit) {
        l = l->left;
        r = r->right;
        std::cout << r->val << l->val << " ";
        if (r->right == nullptr) exit = true;
        if (!l) exit = true;
    }
    std::cout << std::endl;
}
/*
Node* tree::find(int _val) {
    Node* p =first;
    while (p && p->val != _val)  p->next;
    return (p && p->val == _val) ? p : nullptr;
}

void tree::remove_first() {
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}

void tree::remove_last() {
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

void tree::remove(int _val) {
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

Node* tree::operator[](const int index) {
    if (is_empty()) return nullptr;
    Node* p = first;
    for ( int count = 0; count < index; count++) {
        p = p->next;
        if (!p) return nullptr;
    }
    return p;
}
*/

int main()
{
    tree l;
    std::cout << l.is_empty() << std::endl;
    l.push(3);
    l.push(12);
    l.push(80);
    l.print();
    std::cout << l.is_empty() << std::endl;
    /*l.remove(123);
    l.print();
    l.push_back(1234);
    l.remove_first();
    l.print();
    l.remove_last();
    l.print();
    std::cout << l[10]->val << std::endl;*/
    return 0;
}
