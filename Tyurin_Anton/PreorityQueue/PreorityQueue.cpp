#include <iostream>

const unsigned int MAX_PRIORITY = 3;

class PQueue;

class Node {
    friend class PQueue;
protected:
    Node *next;
    std::string data;
    unsigned int priority;
public:
    Node(std::string data) : data(data), next(nullptr),priority(1) {}
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

void PQueue::push(std::string data, unsigned int p){ // добавить пeремещение по приоритету вперед
    Node *local = new Node(data);
    if(p > MAX_PRIORITY){
        std::cout << "Maximal preority is " << MAX_PRIORITY << std::endl;
        p = MAX_PRIORITY;
    }
    if (is_empty()) {
        head = local;
        tail = local;
        tail->priority = p;
        size++;
        return;
    }
    Node* local1 = tail;
    while(p > local1->next)
    for (unsigned int idx = 0; idx < size; idx++){
        for (unsigned int pty = 1; pty < MAX_PRIORITY; pty++){

        }
    }
    tail->next = local;
    tail = local;
    tail->priority = p;
    size++;
}

void PQueue::print() {
    if (is_empty()) {return;}
    Node *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

void PQueue::pop() {
    if (is_empty()) return;
    Node* local = head;
    head = local->next;
    delete local;
    size--;
}

int main(){
    PQueue PQueue;
    PQueue.print();
    PQueue.push("he",1);
    PQueue.push("ll",2);
    PQueue.push("ow",2);
    PQueue.push(" ",2);
    PQueue.push("wo",2);
    PQueue.push("rl",2);
    PQueue.push("d",1);
    PQueue.print();

    PQueue.pop();
    PQueue.print();
    PQueue.pop();
    PQueue.print();
    PQueue.pop();
    PQueue.print();
    return 0;
}