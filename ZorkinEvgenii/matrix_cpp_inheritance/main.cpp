#include <iostream>
#include "Matrix.h"

unsigned long int MatrixMemory::total_memory = 0;  // инициализация статического атрибута класса Тотал мемори которая хранится отдельно и к ней каждый Объект (матрицы) класса будет обращаться

int main() {

    std::cout << "Hello\n" << std::endl;

    double ret1[4]={1,2,
                    3,4};

    double ret2[4]={2,4,
                    8,20};

    Matrix A = {2,2};
    A.fill_from_array(ret1); // задание матрицы через массив \присвоить массив

    std::cout << A[1][1] << std::endl; // не забываем что начало с 0, получили 2 строку 2 столбец

    std::cout << A << std::endl;


    Matrix B = {2,2};
    std::cin >> B; // ввод руками матрицы

    B.print();


    return 0;

};
