#include <iostream>
#include "LinkedList.h"

void testMyList() {
    LinkedList<int> list;

    std::cout << "list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Заполнение list с помощью push_head --\n\n";
    for (int i = 1; i < 11; ++i) {
        list.push_head(i);
    }

    std::cout << "а теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Опустошение list с помощью pop_head --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_head()->data << " ";
    }

    std::cout << "\n\nа сейчас list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Заполнение list с помощью push_head --\n";
    for (int i = 1; i < 11; ++i) {
        list.push_head(i);
    }

    std::cout << "\nа теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\nПервый элемент list: ";
    std::cout << list.get_head()->data << '\n';

    // push_next
    list.push_next(100, 3);
    list.push_next(100, 1);
    list.push_next(100, 6);
    std::cout << "\n-- Опустошение list с помощью pop_head --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_head()->data << " ";
    }

    std::cout << "\n-- Заполнение list с помощью push_head --\n";
    for (int i = 1; i < 11; ++i) {
        list.push_head(i);
    }

    std::cout << "\nа теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    list.delete_next(2);
    list.delete_next(3);
    list.delete_next(4);
    std::cout << "\n-- Опустошение list с помощью pop_head --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_head()->data << " ";
    }

}

int main() {
    system("chcp 65001");
    testMyList();
    return 0;
}