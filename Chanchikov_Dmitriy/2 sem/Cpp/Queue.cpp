#include <iostream>
#include "Linked List.h"

class Queue {
private:
    LinkedList list;

public:
    void push(double val) {
        list.push_tail(val);
    }

    double pop() {
        return list.pop_head();
    }

    double get() {
        return list.get_head();
    }

    void print() {
        list.print("Queue");
    }
};

int main() {
    Queue queue;

    // Добавление элементов в конец списка
    queue.push(-1.2);
    queue.push(3.4);
    queue.push(-5.6);
    queue.push(7.8);

    queue.print();

    // Получение значения первого элемента списка без его удаления
    std::cout << "First element: " << queue.get() << std::endl;

    // Извлечение первых элементов списка
    std::cout << "Deleted element: " << queue.pop() << std::endl;
    std::cout << "Deleted element: " << queue.pop() << std::endl;

    queue.print();

    // Извлечение первых элементов списка
    std::cout << "Deleted element: " << queue.pop() << std::endl;
    std::cout << "Deleted element: " << queue.pop() << std::endl;

    queue.print();

    return 0;
}
