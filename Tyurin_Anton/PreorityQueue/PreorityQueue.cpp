#include <iostream>

const unsigned int MAX_PREORITY = 3;

template<typename T>
class PQueue;

template<typename T>
class Node {
    friend class PQueue<T>;
protected:
    Node<T> *next;
    T data;
    unsigned int preority;
public:
    Node(T _data) : data(_data), next(nullptr),preority(0) {}
};

template<typename T>
class PQueue {
protected:
    Node<T> *first_el;
    Node<T> *last_el;
    unsigned int size;
public:
    PQueue() : first_el(nullptr), last_el(nullptr), size(0) {}
    bool is_empty();
    void push(T _data, unsigned int preority);
    void print();
    void pop();
    void remove_first();
    unsigned int get_size();
    void remove_last();
    Node<T> *operator[](const uint64_t index);
};

template <typename T>
bool PQueue<T>::is_empty() {
    return first_el == nullptr;
}
template<typename T>
void PQueue<T>::remove_first() {
    if (is_empty()) return;
    Node<T>* local = first_el;
    first_el = local->next;
    delete local;
    size--;
}

template<typename T>
void PQueue<T>::remove_last() {
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

template <typename T>
void PQueue<T>::push(T _data, unsigned int p){ // добавить епремещение по приоритету вперед
    Node<T> *local = new Node<T>(_data);
    if(p > MAX_PREORITY){
        std::cout << "Maximal preority is " << MAX_PREORITY << std::endl;
        p = MAX_PREORITY;
    }
    if (is_empty()) {
        first_el = local;
        last_el = local;
        last_el->preority = p;
        size++;
        return;
    }
    last_el->next = local;
    last_el = local;
    last_el->preority = p;
    size++;
}



template<typename T>
void PQueue<T>::print() {
    if (is_empty()) {return;}
    Node<T> *local = first_el;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
Node<T> *PQueue<T>::operator[](const uint64_t index) {
    Node<T>* node = first_el;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node;
}

template<typename T>
void PQueue<T>::pop() { //  станет проще
    if (is_empty()) return;
    Node<T>* local;
    for (unsigned int P = 1; P < MAX_PREORITY; P++) {
        local = first_el;
        for (unsigned int idx = 0; idx < size; idx++) {
            if (P == local->preority){
                if (0 == idx ) {
                    remove_first();
                    return;
                }
                else if (idx + 1 == size) {
                    remove_last();
                    return;
                }
                local = this->operator[](idx - 1);
                local->next = local->next->next;
                size--;
                return;
            }
            local = local->next;
        }
    }
}

int main(){
    PQueue<std::string> PQueue;
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