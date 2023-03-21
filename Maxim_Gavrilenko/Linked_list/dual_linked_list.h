//
// Created by El1x3r7714 on 21/03/2023.
//

#ifndef MR2022_DUAL_LINKED_LIST_H
#define MR2022_DUAL_LINKED_LIST_H

#include <iostream>

class Node {
public:
    int data;
    Node* prev;
    Node* next;
};

class LinkedList {
private:

    int size;
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // добавление элемента в конец списка
    void push_tail(int data) {
        Node* node = new Node{ data, tail, nullptr };
        if (tail) {
            tail->next = node;
        }
        tail = node;
        if (!head) {
            head = node;
        }
        size++;
    }

    // добавление элемента в начало списка
    void push_head(int data) {
        Node* node = new Node{ data, nullptr, head };
        if (head) {
            head->prev = node;
        }
        head = node;
        if (!tail) {
            tail = node;
        }
        size++;
    }

    void remove(int value) {
        Node* current = head;
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
    }

    /*// удаление элемента из списка
    void remove(Node* node) {
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
    }*/

    // получение элемента списка по индексу
    Node* get_node(int index) const {
        if (index < 0) {
            return nullptr;
        }
        Node* node = head;
        for (int i = 0; node && i < index; i++) {
            node = node->next;
        }
        return node;
    }

    // вывод списка на экран
    void print() const {
        Node* node = head;
        while (node) {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << std::endl;
    }

    int& operator[](unsigned int idx)
    {
    unsigned int i = 0;
    Node* current = this->head;
    while(current) {
        if (i == idx) {
            return current->data;
        }
        current = current->next;
        i++;
    }
    }
};


#endif //MR2022_DUAL_LINKED_LIST_H
