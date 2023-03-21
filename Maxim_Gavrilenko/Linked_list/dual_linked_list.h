
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


    unsigned int get_size() {return size;}
    void push_tail(T data);
    void push_head(T data);
    T pop_head();
    T pop_tail();
    void remove(T value);
    void remove(Node<T>* node);
    void clear();
    void insert(Node<T>*, T);
    Node<T>* get_node(unsigned int index) const; // получение элемента списка по индексу
    T& operator[](unsigned int idx);

};

template <typename T>
void LinkedList<T>::insert(Node<T>* node, T data)
{
    if (node == head)
    {
        push_head(data);
        return;
    }
    node->prev->next = new Node<T>{data, node->prev->prev, node->prev->next};
    if (!node->prev->next) throw BADALLOC;
    size++;
    node->prev = nullptr;
}

template <typename T>
T LinkedList<T>::pop_head()
{
    if (size == 0) throw EMPTY;
    T element = head->data;
    head->next->prev = nullptr;
    head = head->next;
    size--;
    return element;
}

template <typename T>
T LinkedList<T>::pop_tail()
{
    if (size == 0) throw EMPTY;
    T element = tail->data;
    tail->prev->next = nullptr;
    tail = tail->prev;
    size--;
}

template <typename T>
void LinkedList<T>::clear()
{
    while(size)
    {
        pop_head();
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
    Node<T>* node = new Node<T>{ data, tail, nullptr};
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
    Node<T>* node = new Node<T>{data, nullptr, head};
    if (!node) throw BADALLOC;
    if (head)
    {
        head->prev = node;
    }
    head = node;
    if (!tail)
    {
        tail = node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::remove(T value) {
    Node<T> *current = head;
    // Поиск элемента с заданным значением
    while (current != nullptr && current->data != value) {
        current = current->next;
    }
    // Если элемент найден, удаляем его
    if (current != nullptr) {
        // Если удаляемый элемент - начальный элемент списка, обновляем указатель head
        if (current == head) {
            head = current->next;
        }
        // Если удаляемый элемент - конечный элемент списка, обновляем указатель tail
        if (current == tail) {
            tail = current->prev;
        }
        // Обновляем указатели на соседние элементы
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        // Удаляем узел
        delete current;
    }
    size--;
}

template <typename T>
void LinkedList<T>::remove(Node<T> *node)
{
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

template <typename T>
Node<T>* LinkedList<T>::get_node(unsigned int index) const
{
    if (index >= size) throw OUTOFRANGE;
    Node<T>* node = head;
    for (int i = 0; node && i < index; i++)
    {
        node = node->next;
    }
    return node;
}


template <typename T>
T& LinkedList<T>::operator[](unsigned int idx)
{
    unsigned int i = 0;
    Node<T>* current = this->head;
    while(current)
    {
        if (i == idx)
        {
        return current->data;
        }
        current = current->next;
        i++;
    }
}
#endif //MR2022_DUAL_LINKED_LIST_H
