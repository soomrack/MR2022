
#ifndef MR2022_DUAL_LINKED_LIST_H
#define MR2022_DUAL_LINKED_LIST_H

#include <iostream>
class LIST_ERROR: public std:: domain_error
{
public:
    LIST_ERROR(const char* const str): std::domain_error(str) {};

};
LIST_ERROR OUTOFRANGE("Out of range");
LIST_ERROR EMPTY("List is empty");
LIST_ERROR BADALLOC("Memory has not been allocated");

template <typename T>
class Node {
public:

    T data;
    Node* prev;
    Node* next;
    Node(const T& value, Node* prev = nullptr, Node* next = nullptr): data(value), prev(prev), next(next) {}
};

template <typename T>
class Iterator {
public:
    Iterator(Node<T>* node_it) : node(node_it) {}
    Iterator operator++() {
        node = node->next;
            return *this; }
    bool operator!=(const Iterator& other) { return node != other.node; }
    T& operator*() { return node->data; }
    Node<T>* get_node() const {return node;}
private:
    Node<T>* node;
};

template <typename T>
class LinkedList {
private:

    unsigned int size;
    Node<T>* head;
    Node<T>* tail;


public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~LinkedList();

    Iterator<T> begin() { return Iterator(head);}
    Iterator<T> end() {return Iterator(tail);}
    unsigned int get_size() {return size;}
    void push_tail(T data);
    void push_head(T data);
    void pop_head();
    void pop_tail();
    void remove(Iterator <T>);
    void clear();
    void insert(Iterator<T>&, const T);
};

template <typename T>
void LinkedList<T>::insert(Iterator<T>& pos, const T data)
{
    Node<T>* node = new Node(data);
    Node<T>* it = pos.get_node(); // Получаем указатель на текущий узел
    node->prev = it->prev;
    node->next = it;
    if (it->prev) {
        it->prev->next = node;
    } else {
        head = node;
    }
    it->prev = node;
    size++;
}

template <typename T>
void LinkedList<T>::pop_head()
{
    if (size == 0) throw EMPTY;
    Node<T>* node = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete node;
    size--;
}

template <typename T>
void LinkedList<T>::pop_tail()
{
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    }
    size--;
}

template <typename T>
void LinkedList<T>::clear()
{
    while(size)
    {
        pop_tail();
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* current = head;
    while (current)
    {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void LinkedList<T>::push_tail(T data)
{
    auto* node = new Node<T>{ data, tail, nullptr};
    if (!node) throw BADALLOC;
    if (tail) {
        tail->next = node;
    }
    tail = node;
    if (!head) {
        head = node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::push_head(T data)
{
    auto* node = new Node(data);
    if (head == nullptr) {
        head = tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::remove(Iterator<T> pos)
{
    if(size == 0) throw EMPTY;
    Node<T>* node = pos.get_node();
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }
    delete node;
    size--;
}

#endif //MR2022_DUAL_LINKED_LIST_H
