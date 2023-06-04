#include <iostream>

class Stack;

class Node {
    friend class Stack;
protected:
    Node *next;
    Node *previous;
    std::string data;
public:
    Node(std::string data) : data(data), next(nullptr), previous(nullptr){}
};

class Stack {
protected:
    Node *head;
    Node *tail;
    unsigned int size;
public:
    Stack() : head(nullptr), tail(nullptr), size(0) {}
    bool is_empty();
    void push(std::string data);
    void print();
    std::string pop();
    unsigned int get_size();
};

bool Stack::is_empty() {
    return head == nullptr;
}

void Stack::push(std::string data){
    Node *local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    head->previous = local;
    local->next = head;
    head = local;
    size++;
}

void Stack::print() {
    if (is_empty()) {return;}
    Node *local = head;
    while (local) {
        std::cout << local->data << std::endl;
        local = local->next;
    }
    std::cout << std::endl;
}

std::string Stack::pop() {
    if (is_empty()) return "";
    if (head == tail) {
        auto local = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
        return local;
    }
    auto local = head->data;
    delete head->previous;
    head = head->next;
    size--;
    return local;
}

unsigned int Stack::get_size() {
    return size;
}


int main(){
    Stack Stack;
    Stack.print();
    Stack.push("he");
    Stack.push("ll");
    Stack.push("ow");
    Stack.push(" ");
    Stack.push("wo");
    Stack.push("rl");
    Stack.push("d");
    Stack.print();

    Stack.pop();
    Stack.pop();

    Stack.print();

    return 0;
}
