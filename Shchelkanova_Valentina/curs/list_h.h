#ifndef list_h
#define list_h

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* next;
};

// Определяем класс списка
class List {
private:
    Node* head;
    Node* tail;

public:
    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    void push_tail(int value);      // Добавление элемента в конец списка
    void display() const;           // Вывод списка
    void push_head(int value);      // Добавление элемента в начало списка
    void delete_head();             // Удаление первого элемента списка
    void delete_tail();             // Удаление последнего элемента списка
    void delete_position(int pos);  // Удаление элемента на указанной позиции
    void fillWithRandom();          // Заполнение списка случайными числами
    void clearList();               // Очистка списка
    Node* get_head() const;         // Возвращение указателя на первый элемент
    int searchElementPosition(int element);
};

List::List() {
    head = nullptr;
    tail = nullptr;
}

List::List(const List& other) {
    head = nullptr;
    tail = nullptr;
    Node* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}
void List::clearList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}


List& List::operator=(const List& other) {
    if (this != &other) {
        clearList();
        Node* current = other.head;
        while (current != nullptr) {
            push_tail(current->data);
            current = current->next;
        }
    }
    return *this;
}

List::~List() {
    clearList();
}

void List::push_tail(int value) {
    Node* temp = new Node;
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

void List::display() const {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << "\t";
        temp = temp->next;
    }
}

void List::push_head(int value) {
    Node* temp = new Node;
    temp->data = value;
    temp->next = head;
    head = temp;
}

void List::delete_head() {
    if (head == nullptr) {
        return;
    }
    Node* temp = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
}

void List::delete_tail() {
    if (head == nullptr) {
        return;
    }
    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }
    Node* current = head;
    while (current->next != tail) {
        current = current->next;
    }
    delete tail;
    tail = current;
    tail->next = nullptr;
}

void List::delete_position(int pos) {
    if (pos < 1) {
        return;
    }
    if (pos == 1) {
        delete_head();
        return;
    }
    Node* current = head;
    Node* previous = nullptr;
    for (int i = 1; i < pos; i++) {
        if (current == nullptr) {
            return;
        }
        previous = current;
    }}

int List::searchElementPosition(int element) {
    int position = 1;
    Node* current = head;
    while (current != nullptr) {
        if (current->data == element) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}


#endif  // list_h