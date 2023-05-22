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
    Node* head;
    Node* tail;
public:
    queue() : head(nullptr), tail(nullptr) {}

    bool is_empty() ;
    void push(int _val);
    void print();
    int pop() ;
};

class Exception : public std::domain_error
{
public:
    Exception(const char* const message) : std::domain_error(message)
    {}
};

Exception empty("queue is empty");



bool queue::is_empty() {
    return head == nullptr;
}

void queue::push(int _val) {
    Node* el = new Node(_val);
    if (is_empty()) {
        head = el;
        tail = el;
        return;
    }
    tail->next = el;
    tail = el;

}

void queue::print() {
    if (is_empty()) return;
    Node* el = head;
    while (el) {
        std::cout << el->val << " ";
        el = el->next;
    }
    std::cout << std::endl;
}



int queue::pop() {
    if (is_empty()) throw empty;
    Node* el = head;
    int head_val = el->val;
    head = el->next;
    delete el;
    return head_val;
}


int main()
{
    queue A;
    A.push(1);
    std::cout<< "is empty?" << A.is_empty() << std::endl;
    A.push(2);
    A.print();
    A.push(3);
    A.pop();
    A.print();
    return 0;
}
