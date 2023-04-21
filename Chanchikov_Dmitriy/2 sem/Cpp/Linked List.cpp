#include <iostream>

class Item {
public:
    explicit Item(double val) : data(val), next(nullptr), prev(nullptr) {}

    double data;
    Item* next;
    Item* prev;
};

class LinkedList {
private:
    Item* head;
    Item* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    void push_head(double val);
    void push_tail(double val);

    double pop_head();
    double pop_tail();
    //void pop(double val);

    double get_head() const;
    double get_tail() const;

    void print();
};

// Добавление элемента в начало списка
void LinkedList::push_head(double val) {
    Item* new_item = new Item(val);
    if (!head) {
        head = tail = new_item;
    } else {
        head->prev = new_item;
        new_item->next = head;
        head = new_item;
    }
}

// Добавление элемента в конец списка
void LinkedList::push_tail(double val) {
    Item* new_item = new Item(val);
    if (!head) {
        head = tail = new_item;
    } else {
        tail->next = new_item;
        new_item->prev = tail;
        tail = new_item;
    }
}

// Удаление первого элемента списка и возвращение его значение
double LinkedList::pop_head() {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    double value = head->data;
    Item* tmp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete tmp;
    return value;
}

// Удаление последнего элемента списка и возвращение его значение
double LinkedList::pop_tail() {
    if (!tail) {
        throw std::runtime_error("List is empty");
    }
    double value = tail->data;
    Item* tmp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete tmp;
    return value;
}

// Удаление элемента по значению
/*
void LinkedList::pop(double val) {
    Item* current = head;
    while (current) {
        if (current->data == val) {
            if (current == head && current == tail) {
                head = tail = nullptr;
            } else if (current == head) {
                head = head->next;
                head->prev = nullptr;
            } else if (current == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            } else {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}
*/

// Получение значения первого элемента списка без его удаления
double LinkedList::get_head() const {
    if (!head) {
        throw std::runtime_error("List is empty");
    }
    return head->data;
}

// Получение значения последнего элемента списка без его удаления
double LinkedList::get_tail() const {
    if (!tail) {
        throw std::runtime_error("List is empty");
    }
    return tail->data;
}

// Вывод элементов списка
void LinkedList::print() {
    Item* current = head;
    std::cout << "List: ";
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

int main() {
    LinkedList list;

    // Добавление элементов в начало и конец списка
    list.push_head(2.5);
    list.push_head(-1.8);
    list.push_tail(3.789);
    list.push_tail(5.0);

    list.print();

    // Извлечение первого и последнего элементов списка
    double head_del_val = list.pop_head();
    double tail_del_val = list.pop_tail();

    std::cout << "First deleted element: " << head_del_val << std::endl;
    std::cout << "Last deleted element: " << tail_del_val << std::endl;

    list.print();

    // Получение значения первого и последнего элементов списка без их удаления
    double head_val = list.get_head();
    double tail_val = list.get_tail();

    std::cout << "First element: " << head_val << std::endl;
    std::cout << "Last element: " << tail_val << std::endl;

    return 0;
}
