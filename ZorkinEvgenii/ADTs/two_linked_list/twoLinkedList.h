#ifndef PROGRAMMING_LIST_H
#define PROGRAMMING_LIST_H

#include <iostream>

namespace list {

    template<class T>
    struct Node {
        Node<T> *next;
        Node<T> *prev;
        T element;
    };


    template<class T>
    class List {
    private:
        Node<T> *list_head;
        Node<T> *list_tail;

        unsigned long long list_size;

    public:
        List(T *array, unsigned long long array_length);

        void push_back(const T &element);

        void push_front(const T &element);

        void push_back(const List<T> &list);

        void push_front(const List<T> &list);

        T pop_back();

        T pop_front();

        T &head() { return list_head->element; }

        T &tail() { return list_tail->element; }

        unsigned long long size() { return size; }

        bool empty() { return (bool) list_size; }
    };


    template<typename T>
    List<T>::List(T *array, unsigned long long array_length) {
        list_size = 0;
        for (unsigned long long idx = 0; idx < array_length; idx++) this->push_back(array[idx]);
    }


    template<typename T>
    void List<T>::push_back(const T &element) {
        auto new_element = new Node<T>(list_tail, nullptr, element);
        if (list_size == 0) list_head = new_element;
        else list_tail->next = new_element;
        list_tail = new_element;
        list_size++;
    }


    template<typename T>
    void List<T>::push_front(const T &element) {
        auto new_element = new Node<T>(nullptr, list_head, element);
        if (list_size == 0) list_tail = new_element;
        else list_head->prev = new_element;
        list_head = new_element;
        list_size++;
    }


    template<typename T>
    void List<T>::push_back(const List<T> &list) {
        List<T> new_list = list;
        new_list.list_head->prev = list_tail;
        list_tail->next = new_list.list_head;
        list_tail = new_list.list_tail;
    }


    template<typename T>
    void List<T>::push_front(const List<T> &list) {
        List<T> new_list = list;
        new_list.list_tail->next = list_tail;
        list_tail->prev = new_list.list_tail;
        list_head = new_list.list_head;
    }


    template<typename T>
    T List<T>::pop_back() {
        if (list_size == 0) {
            std::cerr << "Can't pop from empty list" << std::endl;
            exit(1);
        }
        T element = list_tail->element;
        list_tail->prev->next = nullptr;
        list_tail = list_tail->prev;
        return element;
    }


    template<typename T>
    T List<T>::pop_front() {
        if (list_size == 0) {
            std::cerr << "Can't pop from empty list" << std::endl;
            exit(1);
        }
        T element = list_head->element;
        list_head->next->prev = nullptr;
        list_head = list_head->next;
        return element;
    }
}

#endif //PROGRAMMING_LIST_H
