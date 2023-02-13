#include <iostream>
#include "library.cpp"

using namespace std;

int main(int argc, char* argv[])
{
    // русский язык в консоли
    system("chcp 65001");

    // Создание матриц
    Matrix mat1(3, 3);
    Matrix mat2(3, 3);
    Matrix mat3(4, 3);
    Matrix mat4(3, 4);

    // Матрицы для хранения результатов сложения, умножения и т.д.
    Matrix matSum;
    Matrix matSub;
    Matrix matMul;
    Matrix matMulScal;
    Matrix matTrans;
    Matrix matExp;

    // Заполнение матриц
    // Заполнение матриц
    // mat1
    {
        mat1.getValue(0, 0) = 4.0f;
        mat1.getValue(0, 1) = 3.0f;
        mat1.getValue(0, 2) = -7.0f;

        mat1.getValue(1, 0) = -5.0f;
        mat1.getValue(1, 1) = -6.0f;
        mat1.getValue(1, 2) = 0.0f;

        mat1.getValue(2, 0) = -1.0f;
        mat1.getValue(2, 1) = 2.0f;
        mat1.getValue(2, 2) = 3.0f;

    }
    // mat2
    {
        mat2.getValue(0, 0) = 1.0f;
        mat2.getValue(0, 1) = -2.0f;
        mat2.getValue(0, 2) = -3.0f;

        mat2.getValue(1, 0) = 3.0f;
        mat2.getValue(1, 1) = -1.0f;
        mat2.getValue(1, 2) = 9.0f;

        mat2.getValue(2, 0) = -7.0f;
        mat2.getValue(2, 1) = 6.0f;
        mat2.getValue(2, 2) = 7.0f;

    }
    // mat3
    {
        mat3.getValue(0, 0) = 4.0f;
        mat3.getValue(0, 1) = 3.0f;
        mat3.getValue(0, 2) = -7.0f;

        mat3.getValue(1, 0) = -5.0f;
        mat3.getValue(1, 1) = -6.0f;
        mat3.getValue(1, 2) = 0.0f;

        mat3.getValue(2, 0) = -1.0f;
        mat3.getValue(2, 1) = 2.0f;
        mat3.getValue(2, 2) = 3.0f;

        mat3.getValue(3, 0) = -9.0f;
        mat3.getValue(3, 1) = -6.0f;
        mat3.getValue(3, 2) = 7.0f;

    }
    // mat4
    {
        mat4.getValue(0, 0) = 1.0f;
        mat4.getValue(0, 1) = 5.0f;
        mat4.getValue(0, 2) = -1.0f;
        mat4.getValue(0, 3) = 2.0f;

        mat4.getValue(1, 0) = 4.0f;
        mat4.getValue(1, 1) = 3.0f;
        mat4.getValue(1, 2) = -1.0f;
        mat4.getValue(1, 3) = 2.0f;

        mat4.getValue(2, 0) = -3.0f;
        mat4.getValue(2, 1) = 4.0f;
        mat4.getValue(2, 2) = 4.0f;
        mat4.getValue(2, 3) = -1.0f;

    }

    // Вывод изначальных матриц
    printf("Матрица mat1: \n");
    cout << mat1 << endl;
    printf("Матрица mat2: \n");
    cout << mat2 << endl;
    printf("Матрица mat3: \n");
    cout << mat3 << endl;
    printf("Матрица mat4: \n");
    cout << mat4 << endl;

    // Тестирование операций над матрицами
    printf("Определитель матрицы mat1 = %f\n", mat1.determ(mat1.getRows()));
    printf("Определитель матрицы mat2 = %f\n", mat2.determ(mat2.getRows()));

    printf("\nСложение матриц mat1 и mat2: \n");
    matSum = mat1 + mat2;
    cout << matSum;

    printf("\nВычитание матриц mat1 и mat2: \n");
    matSub = mat1 - mat2;
    cout << matSub;

    printf("\nУмножение матриц mat3 и mat4: \n");
    matMul = mat3 * mat4;
    cout << matMul;

    printf("\nУмножение матрицы mat1 на число 10: \n");
    matMulScal = mat1 * 10;
    cout << matMulScal;

    printf("\nТранспонирование матрицы mat4: \n");
    matTrans = mat4.transpose();
    cout << matTrans;

    printf("\nМатрица-экспонента матрицы mat1, где N = 10: \n");
    matExp = mat1.exponent(10);
    cout << matExp;

    return 0;
}