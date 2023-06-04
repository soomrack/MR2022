#include <iostream>
#include "Matrix.h"

unsigned long int MatrixMemory::total_memory = 0;  // инициализация статического атрибута класса Тотал мемори которая хранится отдельно и к ней каждый Объект (матрицы) класса будет обращаться

int main() {

    std::cout << "Hello\n Primer 1 - create matrix A" << std::endl;

    double ret1[4]={1,2,
                    3,4};

    double ret2[4]={2,4,
                    8,20};

    Matrix A = {2,2};              // объявление матрицы 2 на 2
    A.fill_from_array(ret1);              // задание матрицы через массив - присваиваем массив ret1
    A.print();                                 // вывод матрицы А

    std::cout << "Primer 2 - matrix A - 2 col and 2 row\n" << std::endl;

    std::cout << A[1][1] << std::endl;         // не забываем что начало с 0, получили 2 строку 2 столбец

    std::cout << "Primer 3 - create B" << std::endl;
    Matrix B = {2,2};
    std::cin >> B; // ввод руками матрицы
    B.print();

    std::cout << "Primer 4 - det B" << std::endl;
    B.det();
    std::cout << "det B = " << B.det() << std::endl;

    std::cout << "Primer 5 - A + B =" << std::endl;
    std::cout << " " << A+B << std::endl;


    return 0;

};
