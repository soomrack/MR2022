#include <iostream>
#include "../List/List.h"


template<typename T>
bool List<T>::is_empty() {
    return head == nullptr;
}

template<typename T>
void List<T>::push_tail(T data) {
    auto *local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    tail->next = local;
    tail = local;
    size++;
}

template<typename T>
void List<T>::push_head(T data) {
    Node local = new Node(data);
    if (is_empty()) {
        head = local;
        tail = local;
        size++;
        return;
    }
    local->next = head;
    head = local;
    size++;
}

template<typename T>
void List<T>::print() {
    if (is_empty()) { return; }
    auto *local = head;
    while (local) {
        std::cout << local->data << " ";
        local = local->next;
    }
    std::cout << std::endl;
}

template<typename T>
T List<T>::find(unsigned int id) {
    if (is_empty()) { return nullptr; }
    auto *local = head;
    for (unsigned int idx; idx < id; idx++) {
        local = local->next;
    }
    return local->data;
}

template<typename T>
void List<T>::remove_first() {
    if (is_empty()) return;
    auto *local = head;
    head = local->next;
    delete local;
    size--;
}

template<typename T>
void List<T>::remove_last() {
    if (is_empty()) return;
    if (head == tail) {
        remove_first();
        return;
    }
    auto *local = head;
    while (local->next != tail) local = local->next;
    local->next = nullptr;
    delete tail;
    tail = local;
    size--;
}

template<typename T>
void List<T>::pop(unsigned int id) {
    if (is_empty()) return;
    if (id > size) return;
    if (0 == id) {
        remove_first();
        return;
    } else if (id + 1 == size) {
        remove_last();
        return;
    }
    auto *local = head;
    for (int idx = 0; idx < id - 1; idx++) {
        local = local->next;
    }
    local->next = local->next->next;
    size--;
}

template<typename T>
unsigned int List<T>::get_size() {
    return size;
}


int main() {
    List<std::string> List;
    List.print();

    List.push_tail("he");
    List.push_tail("ll");
    List.push_tail("ow");
    List.push_tail(" ");
    List.push_tail("wo");
    List.push_tail("rl");
    List.push_tail("d");
    List.print();
    std::cout << List.get_size() << std::endl;
    List.find(4);
    List.pop(4);
    List.print();

    return 0;
}
