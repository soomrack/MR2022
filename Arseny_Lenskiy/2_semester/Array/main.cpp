#include <iostream>
#include "../heap_sorts_cw/DynamicArray.h"

int main() {

    // объявляем первый динамический массив
    DynamicArray<int> digits;

    // заполняем массив значениями от 1 до 10, используя push_tail()
    for (int i = 1; i <= 10; ++i) {
        digits.push_tail(i);
    }

    // выводим все элементы массива в поток cout
    std::cout << "DIGITS:\t\t";
    digits.print(std::cout);
    std::cout << '\n';

    // укорачиваем максимально допустимый размер массива на 10
    // тут capacity = 15, поэтому 5 элементов должно остаться
    digits.shrink(10);

    // выводим все элементы массива в поток cout
    std::cout << "DIGITS:\t\t";
    digits.print(std::cout);
    std::cout << '\n';

    // объявляем второй динамический массив
    DynamicArray<int> digits2(10);

    // заполняем новый массив значениями, хранящимися в старом,
    // но только в обратном порядке, используя push_head()
    for (int i = 0; i < digits.getSize(); ++i) {
        digits2.push_head(digits[i]);
    }

    // выводим все элементы второго массива в поток cout
    std::cout << "DIGITS_2:\t";
    digits2.print(std::cout);
    std::cout << '\n';

    // присваиваем значения второго массива элементам первого
    digits = digits2;

    // выводим все элементы первого массива в поток cout
    std::cout << "DIGITS:\t\t";
    digits.print(std::cout);
    std::cout << '\n';

    return 0;
}
