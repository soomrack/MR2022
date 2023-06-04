#ifndef MR2022_DUAL_LINKED_LIST_H
#define MR2022_DUAL_LINKED_LIST_H

#include <iostream>
class LIST_ERROR : public std::domain_error
{
public:
    explicit LIST_ERROR(const char *const str) : std::domain_error(str){};
};
LIST_ERROR OUTOFRANGE("Out of range");
LIST_ERROR EMPTY("List is empty");
LIST_ERROR BADALLOC("Memory has not been allocated");


template <typename T> 
class Node
{
public:
    T data;
    Node* prev;//
    Node* next;//
    Node(const Node &other) : data(other.data), prev(nullptr), next(nullptr) {}
    explicit Node(const T &value, Node *prev = nullptr, Node *next = nullptr) : data(value), prev(prev), next(next) {}
};

template <typename T>
class Iterator
{
private:
    Node<T> *node;

public:
    explicit Iterator(Node<T> *node_it) : node(node_it) {}
    Iterator operator++()//--
    {
        node = node->next;
        return *this;
    }
    bool operator!=(const Iterator &other) { return node != other.node; }
    T &operator*() { return node->data; }
    Node<T> *get_node() const { return node; }
};


template <typename T>
class LinkedList
{
private:
    size_t size;
    Node<T> *head;
    Node<T> *tail;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    LinkedList(const LinkedList &);
    LinkedList(LinkedList &&) noexcept;
    LinkedList<T> &operator=(const LinkedList &);
    LinkedList<T> &operator==(LinkedList &&) noexcept;
    ~LinkedList();

    Iterator<T> begin() { return Iterator<T>(head); }
    Iterator<T> end() { return Iterator<T>(tail); }
    unsigned int get_size() { return size; }
    void push_tail(T data);
    void push_head(T data);
    void pop_head();
    void pop_tail();
    void remove(Iterator<T>);
    void remove(const T &value);
    void clear();
    void insert(Iterator<T> &, T);

    bool is_empty() { return size == 0; }
};

template <typename T>
void LinkedList<T>::insert(Iterator<T> &pos, const T data)
{
    auto *node = new Node<T>(data);
    auto *it = pos.get_node(); // Получаем указатель на текущий узел
    node->prev = it->prev;
    node->next = it->prev->next;
    if (it->prev)
    {
        it->prev->next = node;
    }
    else
    {
        head = node;
    }
    it->prev = node;
    size++;
}

template <typename T>
void LinkedList<T>::pop_head()
{
    if (is_empty())
        throw EMPTY;
    Node<T> *node = head;
    head = head->next;
    if (head)
    {
        head->prev = nullptr;
    }
    else
    {
        tail = nullptr;
    }
    delete node;
    size--;
}

template <typename T>
void LinkedList<T>::pop_tail()
{
    tail = tail->prev;
    if (tail != nullptr)
    {
        tail->next = nullptr;
    }
    size--;
}

template <typename T>
void LinkedList<T>::clear()
{
    while (!is_empty())
    {
        pop_tail();
    }
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T> *current = head;
    while (current)
    {
        Node<T> *next = current->next;
        delete current;
        current = next;
    }
}

template <typename T>
void LinkedList<T>::push_tail(T data)
{
    auto *node = new Node<T>{data, tail, nullptr};
    if (!node)
        throw BADALLOC;
    if (tail)
    {
        tail->next = node;
    }
    tail = node;
    if (!head)
    {
        head = node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::push_head(T data)
{
    auto *node = new Node<T>(data);
    if (head == nullptr)
    {
        head = tail = node;
    }
    else
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    size++;
}

template <typename T>
void LinkedList<T>::remove(Iterator<T> pos)
{
    if (is_empty())
        throw EMPTY;
    Node<T> *node = pos.get_node();
    if (node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        head = node->next;
    }
    if (node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        tail = node->prev;
    }
    delete node;
    size--;
}

template <typename T>
void LinkedList<T>::remove(const T &value)
{
    auto *current = head;
    // Поиск элемента с заданным значением
    while (current != nullptr && current->data != value)
    {
        current = current->next;
    }
    // Если элемент найден, удаляем его
    if (current != nullptr)
    {
        // Если удаляемый элемент - начальный элемент списка, обновляем указатель head
        if (current == head)
        {
            head = current->next;
        }
        // Если удаляемый элемент - конечный элемент списка, обновляем указатель tail
        if (current == tail)
        {
            tail = current->prev;
        }
        // Обновляем указатели на соседние элементы
        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }
        // Удаляем узел
        delete current;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &list) : size(list.size), head(nullptr), tail(nullptr)
{
    Node<T> *current = list.head;
    while (current)
    {
        auto *newNode = new Node<T>(*current);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        current = current->next;
    }
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
{
    if (this == &list)
        return *this;
    Node<T> *current = list.head;
    while (current)
    {
        auto *newNode = new Node<T>(*current);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&list) noexcept : size(list.size), head(list.head), tail(list.tail)
{
    list.size = 0;
    list.head = nullptr;
    list.tail = nullptr;
}

template <typename T>
LinkedList<T> &LinkedList<T>::operator==(LinkedList<T> &&list) noexcept
{
    if (this == &list)
        return *this;
    head = list.head;
    tail = list.tail;
    size = list.size;
    list.head = nullptr;
    list.tail = nullptr;
    list.size = 0;
}

#endif // MR2022_DUAL_LINKED_LIST_H
