#include <iostream>
#include "dual_linked_list.h"
#include <list>
template <typename T>
void print(Iterator<T> it)
{
    while (it.get_node() != nullptr) {
        std::cout << *it << " "; // выводим значение текущего элемента
        ++it; // перемещаем итератор на следующий элемент
    }
    std:: cout << std::endl;
}

int main()
{ 
    LinkedList<double> list;
    list.push_head(3);
    list.push_head(10);
    list.push_head(12);
    list.push_head(67);

    Iterator<double> it = list.begin();
    print(list.begin());

    // Выводим элементы списка
// Вставляем новый элемент со значением 4 перед вторым элементом списка
    ++it;
    list.insert(it, 4);
    ++it;
    print(list.begin());
    list.remove(it);
    ++it;
    print(list.begin());
    std::cout<<list.get_size();
    LinkedList<double> list2 = std::move(list);
    list2.clear();
    list2.push_head(3);
}