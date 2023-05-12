#ifndef list_h
#define list_h

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template<class T>
class Node {
public:
    T data;
    Node* next;
};

// Определяем класс списка
template<class T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    void push_tail(T value);        // Добавление элемента в конец списка
    void display() const;           // Вывод списка
    void push_head(T value);        // Добавление элемента в начало списка
    void delete_head();             // Удаление первого элемента списка
    void delete_tail();             // Удаление последнего элемента списка
    void delete_position(int pos);  // Удаление элемента на указанной позиции
    void fillWithRandom();          // Заполнение списка случайными числами
    void clearList();               // Очистка списка
    Node<T>* get_head() const;      // Возвращение указателя на первый элемент
    int searchElementPosition(T element);
    void get_element(int n, T value);
    void change_element(int pos, T value);
    T get_element(int pos) const;
    int get_size();
    void createList(int size, T value);
};


template<class T>
List<T>::List() {
    head = nullptr;
    tail = nullptr;
}

template<class T>
List<T>::List(const List& other) {
    head = nullptr;
    tail = nullptr;
    Node<T>* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}

template<class T>
void List<T>::clearList() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

template<class T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clearList();
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_tail(current->data);
            current = current->next;
        }
    }
    return *this;
}

template<class T>
List<T>::~List() {
    clearList();
}

template<class T>
void List<T>::push_tail(T value) {
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        tail = temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
}

template<class T>
void List<T>::display() const {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
}

template<class T>
void List<T>::push_head(T value) {
    Node<T>* temp = new Node<T>;
    temp->data = value;
    temp->next = head;
    head = temp;
}

template<class T>
void List<T>::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node<T>* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
}

template<class T>
void List<T>::delete_tail() {
    if (head == nullptr) {
        return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node<T>* current = head;
    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
}

template<class T>
void List<T>::delete_position(int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1) {
        delete_head();
        return;
    }
    Node<T>* current = head;
    Node<T>* previous = nullptr;
    for (int i = 1; i < pos; i++) {
        if (current == nullptr) {
            return;
        }
        previous = current;
    }
}

/*template<class T>
int List<T>::searchElementPosition(T element) {
    int position = 1;
    Node<T> *current = head;
}
*/

template<class T>
void List<T>::change_element(int pos, T value) {
    if (pos < 1) {
        return;
    }
    Node<T>* current = head;
    for (int i = 1; i < pos; i++) {
        if (current == nullptr) {
            return;
        }
        current = current->next;
    }
    current->data = value;
}

template<class T>
T List<T>::get_element(int pos) const {
    if (pos < 1) {
        return T();
    }
    Node<T>* current = head;
    for (int i = 1; i < pos; i++) {
        if (current == nullptr) {
            return T();
        }
        current = current->next;
    }
    return current->data;
}


template<class T>
int List<T>::get_size() {
    int size = 0;
    Node<T>* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }
    return size ;
}

template<class T>
void List<T>::createList(int size, T value) {
    clearList();
    for (int i = 0; i < size; i++) {
        push_tail(value);
    }
}
#endif  // list_h
