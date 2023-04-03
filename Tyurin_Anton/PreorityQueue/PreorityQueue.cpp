#include <iostream>

const unsigned int MAX_PRIORITY = 3;

class PQueue;

class Node {
    friend class PQueue;

protected:
    Node *next;
    Node *previous;
    std::string data;
    unsigned int priority;
public:
    Node(std::string data) : data(data), next(nullptr), previous(nullptr), priority(0) {}
};

class PQueue {
protected:
    Node *head;
    Node *tail;
    unsigned int size;
public:
    PQueue() : head(nullptr), tail(nullptr), size(0) {}

    bool is_empty();

    void push(std::string data, unsigned int priority);

    void print();

    void pop();

    unsigned int get_size();
};

bool PQueue::is_empty() {
    return head == nullptr;
}

void PQueue::push(std::string data, unsigned int p) { // добавить пeремещение по приоритету вперед
    Node *local = new Node(data);
    if (p > MAX_PRIORITY) {
        std::cout << "Maximal preority is " << MAX_PRIORITY << std::endl;
        p = MAX_PRIORITY;
    }
    if (is_empty()) {
        head = local;
        tail = local;
        head->priority = p;
        tail->priority = p;
        size++;
        return;
    }
    if (head->priority < p) {
        local->next = head;
        head->previous = local;
        head = local;
        head->priority = p;
        size++;
        return;
    }
    if (tail->priority >= p) {
        tail->next = local;
        local->previous = tail;
        tail = local;
        tail->priority = p;
        size++;
        return;
    }
    Node *current = tail;
    current->priority = tail->priority;
    while (current->priority < p) {
            current = current->previous;
    }
    local->previous = current;
    local->next = current->next;
    current->next = local;
    size++;
}

void PQueue::print() {
    if (is_empty()) { return; }
    Node *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

void PQueue::pop() {
    if (is_empty()) return;
    Node *local = head;
    head = local->next;
    delete local;
    size--;
}

int main() {
    PQueue PQueue;
    PQueue.push("he", 3);
    PQueue.push("ll", 2);
    PQueue.push("ow", 1);
    PQueue.push("__", 3);
    PQueue.push("wo",1);
    PQueue.push("rl",2);
    PQueue.push("d",1);
    PQueue.print();
    PQueue.pop();
    PQueue.print();
    PQueue.pop();
    PQueue.print();
    return 0;
}