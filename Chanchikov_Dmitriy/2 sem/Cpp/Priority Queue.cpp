#include <iostream>
#include <stdexcept>

class Item {
public:
    explicit Item(double val, int p) : data(val), priority(p), next(nullptr) {}

    double data;
    int priority;
    Item* next;
};

class PriorityQueue {
private:
    Item* head;
    Item* tail;

public:
    PriorityQueue() : head(nullptr), tail(nullptr) {}

    void push(double val, int priority);

    double pop();

    double top() const;

    void print() const;

    bool empty() const {
        return head == nullptr;
    }
};

// Добавление элемента с заданным приоритетом в приоритетную очередь
void PriorityQueue::push(double val, int priority) {
    Item* new_item = new Item(val, priority);
    if (!head) {
        head = tail = new_item;
    } else {
        Item* current = head;
        Item* prev = nullptr;
        while (current && current->priority >= priority) {
            prev = current;
            current = current->next;
        }
        if (prev) {
            prev->next = new_item;
        } else {
            head = new_item;
        }
        new_item->next = current;
        if (!current) {
            tail = new_item;
        }
    }
}

// Удаление элемента с наивысшим приоритетом из приоритетной очереди и возвращение его значения
double PriorityQueue::pop() {
    if (!head) {
        throw std::runtime_error("Queue is empty");
    }
    double value = head->data;
    Item* tmp = head;
    head = head->next;
    if (!head) {
        tail = nullptr;
    }
    delete tmp;
    return value;
}

// Получение значения элемента с наивысшим приоритетом без его удаления
double PriorityQueue::top() const {
    if (!head) {
        throw std::runtime_error("Queue is empty");
    }
    return head->data;
}

void PriorityQueue::print() const {
    Item* current = head;
    std::cout << "Priority Queue: ";
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


int main() {
    PriorityQueue pq;

    pq.push(-5.0, 1);
    pq.push(2.1, 2);
    pq.push(3.33, 2);
    pq.push(4.0, 3);

    pq.print();

    std::cout << "Popped element: " << pq.pop() << std::endl;
    std::cout << "Popped element: " << pq.pop() << std::endl;

    pq.print();

    std::cout << "Top element: " << pq.top() << std::endl;


    return 0;
}
