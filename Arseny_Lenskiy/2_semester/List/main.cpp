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

    std::cout << "\n-- Опустошение list с помощью pop_tail --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_tail() << " ";
    }

    std::cout << "\n\nа сейчас list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Заполнение list с помощью push_tail --\n\n";
    for (int i = 1; i < 11; ++i) {
        list.push_tail(i);
    }

    std::cout << "а теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Опустошение list с помощью pop_tail --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_tail() << " ";
    }

    std::cout << "\n\nа сейчас list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Заполнение list с помощью push_tail --\n\n";
    for (int i = 1; i < 11; ++i) {
        list.push_tail(i);
    }

    std::cout << "а теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Опустошение list с помощью pop_head --\n\n";
    std::cout << "Cодержимое list: ";
    while (!list.is_empty()) {
        std::cout << list.pop_head() << " ";
    }

    std::cout << "\n\nа сейчас list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Заполнение list с помощью push_tail --\n\n";
    for (int i = 1; i < 11; ++i) {
        list.push_tail(i);
    }

    std::cout << "а теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\n-- Просмотр list с помощью get_item --\n\n";
    std::cout << "Cодержимое list: ";
    for (int i = 0; i < list.get_size(); ++i) {
        std::cout << list.get_item(i) << " ";
    }

    std::cout << "\n\nа теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';

    std::cout << "\nПервый элемент list: ";
    std::cout << list.get_head() << '\n';

    std::cout << "Последний элемент list: ";
    std::cout << list.get_tail() << '\n';

    std::cout << "\n-- Опустошение list с помощью clear --\n\n";
    list.clear();

    std::cout << "а теперь list пуст?\n";
    std::cout << list.is_empty() << '\n';
}

int main() {
    system("chcp 65001");
    testMyList();
    return 0;
}