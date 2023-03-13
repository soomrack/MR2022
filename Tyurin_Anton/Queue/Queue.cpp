#include <iostream>

template<typename T>
class Queue;

template<typename T>
class Node {
    friend class Queue<T>;
protected:
    Node<T> *next;
    T data;
public:
    Node(T _data) : data(_data), next(nullptr){}
};

template<typename T>
class Queue {
protected:
    Node<T> *first_el;
    Node<T> *last_el;
    unsigned int size;
public:
    Queue() : first_el(nullptr), last_el(nullptr), size(0) {}
    bool is_empty();
    void push(T _data);
    void print();
    void pop();
    void remove_first();
    unsigned int get_size();
};

template <typename T>
bool Queue<T>::is_empty() {
    return first_el == nullptr;
}

template <typename T>
void Queue<T>::push(T _data){
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
void Queue<T>::print() {
    if (is_empty()) {return;}
    Node<T> *local = first_el;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
void Queue<T>::pop() {
    if (is_empty()) return;
    Node<T>* local = first_el;
    if (local == last_el){ last_el = nullptr;}
    first_el = local->next;
    delete local;
    size--;
}

template<typename T>
unsigned int Queue<T>::get_size() {
    return size;
}


int main(){
    Queue<std::string> Queue;
    Queue.print();
    Queue.push("he");
    Queue.push("ll");
    Queue.push("ow");
    Queue.push(" ");
    Queue.push("wo");
    Queue.push("rl");
    Queue.push("d");
    Queue.print();
    Queue.pop();
    Queue.pop();
    Queue.pop();
    Queue.print();
    return 0;
}