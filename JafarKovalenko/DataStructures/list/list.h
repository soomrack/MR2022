#ifndef LIST_H
#define LIST_H

#include <cstddef>


template<class T>
class Node 
{

    template<class TT> friend class LinkedList;

private:

    Node* prev;
    Node* next;

    Node(T data);

public:

    T data;

};


template<class T>
class LinkedList 
{

public:

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList<T>& other);
    LinkedList<T>& operator=(const LinkedList<T>& other);

    bool operator==(const LinkedList<T>& other) const;
    bool operator!=(const LinkedList<T>& other) const;

    size_t size() const;

    Node<T>* push_back(T data);
    Node<T>* push_front(T data);

    void  delete_back();
    void  delete_front();

    Node<T>* get_node(size_t index);

    Node<T>* insert(size_t index, T data);
    void erase(size_t index);
    void clear();
    bool empty() const;

private:

    Node<T>* head;
    Node<T>* tail;
    size_t size_list;

};



template<class T>
Node<T>::Node(T data)
{
    this->data = data;
    prev = nullptr;
    next = nullptr;
}

template<class T>
LinkedList<T>::LinkedList() 
{
    head = tail = nullptr;
    size_list = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    while (head != nullptr)
        delete_front();
    size_list = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
    : LinkedList()
{
   if (!other.empty())
       for (Node<T>* ptr = other.head; ptr != nullptr; ptr = ptr->next)
           push_back(ptr->data);
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
{
    if (this != &other)
    {
       clear();
       for (Node<T>* ptr = head; ptr != nullptr; ptr = ptr->next)
           push_back(ptr->data);
    }

    return *this;
}

template<class T>
size_t LinkedList<T>::size() const
{
    return size_list; 
}

template<class T>
Node<T>* LinkedList<T>::push_front(T data) 
{
    auto ptr = new Node<T>(data);
    ++size_list;

    ptr->next = head;
    if (head != nullptr)
        head->prev = ptr;

    if (tail == nullptr)
        tail = ptr;

    head = ptr;
    return ptr;
}

template<class T>
Node<T>* LinkedList<T>::push_back(T data) 
{
    auto ptr = new Node<T>(data);
    ++size_list;

    ptr->prev = tail;
    if (tail != nullptr)
        tail->next = ptr;

    if (head == nullptr)
        head = ptr;

    tail = ptr;
    return ptr;
}

template<class T>
void LinkedList<T>::delete_front() 
{
    if (head == nullptr) return;

    auto ptr = head->next;
    if (ptr != nullptr)
        ptr->prev = nullptr;
    else
        tail = nullptr;
    
    --size_list;
    delete head;
    head = ptr;
}

template<class T>
void LinkedList<T>::delete_back() 
{
    if (tail == nullptr) return;

    auto ptr = tail->prev;
    if (ptr != nullptr)
        ptr->next = nullptr;
    else
        head = nullptr;
    
    --size_list;
    delete tail;
    tail = ptr;
}

template<class T>
Node<T>* LinkedList<T>::get_node(size_t index) 
{
    auto ptr = head;

    for (int i = 0; i != index; ++i)
    {
        if (ptr == nullptr)
            return ptr;
        ptr = ptr->next;
    }

    return ptr;
}


template<class T>
Node<T>* LinkedList<T>::insert(size_t index, T data) 
{
    auto right = get_node(index);
    if (right == nullptr)
        return push_back(data);

    auto left = right->prev;
    if (left == nullptr)
        return push_front(data);

    auto ptr = new Node<T>(data);
    ++size_list;

    ptr->prev = left;
    ptr->next = right;
    left->next = ptr;
    right->prev = ptr;

    return ptr;
}

template<class T>
void LinkedList<T>::erase(size_t index) 
{
    auto ptr = get_node(index);
    if (ptr == nullptr)
        return;

    if (ptr->prev == nullptr) {
        delete_front();
        return;
    }

    if (ptr->next == nullptr) {
        delete_back();
        return;
    }

    auto left = ptr->prev;
    auto right = ptr->next;
    left->next = right;
    right->prev = left;
    
    --size_list;
    delete ptr;
}

template<class T>
void LinkedList<T>::clear()
{
    while (head != nullptr)
        delete_front();
}

template<class T>
bool LinkedList<T>::empty() const
{
    return !size_list ? true : false;
}


template<class T>
bool LinkedList<T>::operator==(const LinkedList<T>& other) const
{
    if (other.size() != size_list) return false;
    
    Node<T>* one = head;
    Node<T>* two = other.head;
    double eps = 0.001 * 0.001 * 0.001;

    for (int i = 0; i != size_list; ++i)
    {
        if (one->data - two->data > eps) return false;
        one = one->next;
        two = two->next;
    }

    return true;
}

template<class T>
bool LinkedList<T>::operator!=(const LinkedList<T> &other) const
{
    return !operator==(other);
}

#endif  // LIST_H

