#include <iostream>

template<typename T>
class Stack;

template<typename T>
class Node {
    friend class Stack<T>;
protected:
    Node<T> *next;
    T data;
public:
    Node(T _data) : data(_data), next(nullptr){}
};

template<typename T>
class Stack {
protected:
    Node<T> *first_el;
    Node<T> *last_el;
    unsigned int size;
public:
    Stack() : first_el(nullptr), last_el(nullptr), size(0) {}
    bool is_empty();
    void push(T _data);
    void print();
    void pop();
    void remove_first();
    unsigned int get_size();
};

template <typename T>
bool Stack<T>::is_empty() {
    return first_el == nullptr;
}

template <typename T>
void Stack<T>::push(T _data){
    Node<T> *local = new Node<T>(_data);
    if (is_empty()) {
        first_el = local;
        last_el = local;
        size++;
        return;
    }
    last_el->next = local;
    last_el = local;
    size++;
}

template<typename T>
void Stack<T>::print() {
    if (is_empty()) {return;}
    Node<T> *local = first_el;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
void Stack<T>::remove_first() {
    if (is_empty()) return;
    Node<T>* local = first_el;
    first_el = local->next;
    delete local;
    size--;
}

template<typename T>
void Stack<T>::pop() {
    if (is_empty()) return;
    if (first_el == last_el) {
        remove_first();
        return;
    }
    Node<T>* local = first_el;
    while (local->next != last_el) local = local->next;
    local->next = nullptr;
    delete last_el;
    last_el = local;
    size--;
}

template<typename T>
unsigned int Stack<T>::get_size() {
    return size;
}


int main(){
    Stack<std::string> Stack;
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
    Stack.print();

    return 0;
}