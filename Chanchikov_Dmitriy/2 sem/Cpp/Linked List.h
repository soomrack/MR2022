#ifndef CPP_LINKED_LIST_H
#define CPP_LINKED_LIST_H

class Item {
public:
    explicit Item(double val) : data(val), next(nullptr), prev(nullptr) {}

    double data;
    Item* next;
    Item* prev;
};

class LinkedList {
    friend class PriorityQueue;
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

    void print(const std::string& data);
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
void LinkedList::print(const std::string& data) {
    Item* current = head;
    std::cout << data << ": ";
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

#endif //CPP_LINKED_LIST_H
