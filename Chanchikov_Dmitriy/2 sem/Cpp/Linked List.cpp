#include <iostream>
#include "Linked List.h"

int main() {
    LinkedList list;
    const std::string& data = "List";

    // Добавление элементов в начало и конец списка
    list.push_head(2.5);
    list.push_head(-1.8);
    list.push_tail(3.789);
    list.push_tail(5.0);

    list.print(data);

    // Извлечение первого и последнего элементов списка
    std::cout << "First deleted element: " << list.pop_head() << std::endl;
    std::cout << "Last deleted element: " << list.pop_tail() << std::endl;

    list.print(data);

    // Получение значения первого и последнего элементов списка без их удаления
    std::cout << "First element: " << list.get_head() << std::endl;
    std::cout << "Last element: " << list.get_tail() << std::endl;

    return 0;
}
