#ifndef ADT_LINKED_LIST_H
#define ADT_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <string>

class Linked_list_exception: public std::logic_error
{
public:
    explicit Linked_list_exception(const std::string& message):
            std::logic_error(message)
    {}
};

template<typename N>
class Node {
public:
    explicit Node(N data = N(), Node* next = nullptr) {
        this->data = data;
        this->next = next;
    }

    N data;
    Node* next;
};

template<typename T>
class Linked_list {

private:

    Node<T>* head;

protected:
    Linked_list();
    Linked_list(const Linked_list&);
    ~Linked_list();

    Linked_list& operator=(const Linked_list&);
    bool operator==(const Linked_list&);
    bool operator!=(const Linked_list& other) {return !(this == other);}

    void push_tail(T elem);
    void pop_head();


    void print();

    size_t size;

public:
    void clear();
    size_t get_size() const {return size;}

};

template<typename T>
Linked_list<T>::Linked_list():
        size(0),
        head(nullptr)
{}

template<typename T>
Linked_list<T>::Linked_list(const Linked_list& other):
        size(0),
        head(nullptr)
{
    Node<T>* temp = other.head;
    while (temp != nullptr) {
        push_tail(temp->data);
        temp = temp->next;
    }
}

template<typename T>
Linked_list<T> &Linked_list<T>::operator=(const Linked_list& other) {
    if (this == &other) {
        return *this;
    }
    Linked_list temp(other);
    std::swap(this->size, temp.size);
    std::swap(this->head, temp.head);
    return *this;
}

template<typename T>
void Linked_list<T>::clear() {
    while (size) pop_head();
}

template<typename T>
Linked_list<T>::~Linked_list() {
    clear();
}

template<typename T>
void Linked_list<T>::push_tail(T elem) {
    if (head == nullptr) {
        head = new Node<T>(elem);
    } else {
        Node<T>* temp = this->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new Node<T>(elem);
    }
    size++;
}

template<typename T>
void Linked_list<T>::pop_head() {
    if (head == nullptr)
        throw Linked_list_exception("Queue is empty!");
    Node<T>* temp = head;
    head = head->next;
    delete[] temp;
    size--;
}


template<typename T>
bool Linked_list<T>::operator==(const Linked_list& other) {
    if (this == &other) {
        return true;
    }
    if (this->size != other.size) {
        return false;
    }
    if (this->head != other.head) {
        return false;
    }
    return true;
}

template<typename T>
void Linked_list<T>::print() {
    if (head == nullptr)
        throw Linked_list_exception("Queue is empty!");
    Node<T>* temp = this->head;
    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
    std::cout << std::endl;
}

#endif //ADT_LINKED_LIST_H
