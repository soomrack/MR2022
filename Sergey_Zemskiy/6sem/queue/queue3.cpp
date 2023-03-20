#include <iostream>


class Node {
private:
    friend class queue;
    int val;
    Node* next;
public:
    Node(int new_val) : val(new_val), next(nullptr) {}
};

class queue {
private:
    Node* head;
    Node* tail;
public:
    queue() : head(nullptr), tail(nullptr) {}

    bool is_empty() ;
    void push(int new_val);
    void print();
    int pop() ;
};

class Exception : public std::domain_error
{
public:
    Exception(const char* const message) : std::domain_error(message)
    {}
};

Exception empty("No elements in queue");



bool queue::is_empty() {
    return head == nullptr;
}

void queue::push(int new_val) {
    Node* p = new Node(new_val);
    if (is_empty()) {
        head = p;
        tail = p;
        return;
    }
    tail->next = p;
    tail = p;

}

void queue::print() {
    if (is_empty()) return;
    Node* p = head;
    while (p) {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}



int queue::pop() {
    if (is_empty()) throw empty;//сделать исключение
    Node* p = head;
    int head_val = p->val;
    head = p->next;
    delete p;
    return head_val;
}


int main()
{
    queue l;
    std::cout<< "is empty?" << l.is_empty() << std::endl;
    l.pop();
    l.push(1);
    std::cout<< "is empty?" << l.is_empty() << std::endl;
    l.push(2);
    l.print();
    l.push(3);
    l.pop();
    l.print();
    return 0;
}
