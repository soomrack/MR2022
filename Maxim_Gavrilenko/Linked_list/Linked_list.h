#ifndef MR2022_LINKED_LIST_H
#define MR2022_LINKED_LIST_H
#include <iostream>
class LIST_ERROR: public std:: domain_error
{
public:
    LIST_ERROR(const char* const str): std::domain_error(str) {};

};
LIST_ERROR OUTOFRANGE("Out of range");
LIST_ERROR EMPTY("List is empty");
LIST_ERROR BADALLOC("Memory has not been allocated");

template <typename T = double>
class Node
{
public:
    Node* next;
    T data;

    Node(T data = T(0), Node* next = nullptr)
    {
        this -> data = data;
        this -> next = next;
    }

};

template <typename T>
class List
{
public:
    List();
    ~List();

    void pop_front();
    void pop_back();
    void push_back(T data);
    void push_front(T data);
    void insert(List<T>&, T);
    void clear();
    void remove(List<T> &);
    void advance(List&, unsigned int); //Метод сдвигающий private указатель на n-1 элемент
    int get_size();

    T& operator[](unsigned);
private:
    unsigned int size;
    Node<T> *tail;
    Node<T> *head;
    Node<T> *previous;
};


template <typename T>
List<T>::List()
{
    size = 0;
    head = nullptr;
    previous = nullptr;
    tail = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}

template<typename T>
int List<T>::get_size() {return size;}

template<typename T>
T& List<T>::operator[](const unsigned idx)
{
    if (idx > size) throw OUTOFRANGE;
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

template<typename T>
void List<T>::advance(List<T>& list, unsigned int distance)
{
    if (distance >= size) throw OUTOFRANGE;
    list.previous = list.head;
    if (!distance) return;
    for(int i = 0; i < distance - 1; i++)
    {
        list.previous = list.previous->next;
    }
}
template<typename T>
void List<T>::pop_front()
{
    if (size == 0) throw EMPTY;
    Node<T>* temp = head;
    head = head->next;
    delete temp;
    size--;
}

template<typename T>
void List<T>::push_back(T data)
{
    if(!tail)
    {
        head = new Node<T>(data);
        tail = head;
        if (!head) throw std::bad_alloc();
    }
    else
    {
        while (tail->next != nullptr)
        {
          tail = tail -> next;
        }
        tail->next = new Node<T>(data);
        tail = tail->next;
    }
    size++;
}

template<typename T>
void List<T>::clear()
{
    while(size)
    {
        pop_front();
    }
}

template<typename T>
void List<T>::push_front(T data)
{
    head = new Node<T>(data, head);
    if (!head) throw BADALLOC;
    size++;
}

template<typename T>
void List<T>::remove(List<T>& list)
{
    if (list.previous == list.head)
    {
        pop_front();
        return;
    }
    Node<T>* doDelete = list.previous -> next;
    list.previous -> next = doDelete -> next;
    delete doDelete;
    size--;
    list.previous = nullptr;
}

template<typename T>
void List<T>::pop_back()
{
    if (size == 0) throw OUTOFRANGE;
    Node<T>* current = head;
    Node<T>* temp;
    while(current->next)
    {
        temp = current;
        current = current->next;
    }
    delete tail;
    tail = temp;
    tail->next = nullptr;
    size--;
}

template<typename T>
void List<T>::insert(List<T>& list, T data)
{
    if (list.previous == list.head)
    {
        push_front(data);
        return;
    }
    list.previous->next = new Node<T>(data, previous->next);
    if (!list.previous) throw BADALLOC;
    size++;
    list.previous = nullptr;
}


#endif //MR2022_LINKED_LIST_H
