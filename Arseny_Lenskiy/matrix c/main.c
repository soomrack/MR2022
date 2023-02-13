#include <stdio.h>
#include <stdlib.h>


// Структура матрицы
struct matrix
{
    // Одномерный массив чисел
    float* _data;
    // Кол-во строк
    int _rows;
    // Кол-во столбцов
    int _cols;
};

// Структура matrix передается по ссылке в каждой функции

// Функция выделения памяти для матрицы (создание матрицы)
void matrixMalloc(struct matrix* mat, int rows, int cols);

// Функция освобождения памяти матрицы (удаление матрицы)
void matrixFree(struct matrix* mat);

// Функция вывода на консоль матрицы
void matrixPrint(const struct matrix* mat);

// Функция доступа к элементам матрицы
float* matrixGetValue(const struct matrix* mat, int i, int j);

// Функция сложения матриц
struct matrix matrixSum(const struct matrix* mat1, const struct matrix* mat2);

// Функция вычитания матриц
struct matrix matrixSubtract(const struct matrix* mat1, const struct matrix* mat2);

// Функция умножения матриц
struct matrix matrixMultiply(const struct matrix* mat1, const struct matrix* mat2);

// Функция умножения матрицы на число
struct matrix matrixMultiplyScalar(const struct matrix* mat, float scalar);

// Функция деления матрицы на число
struct matrix matrixDivideScalar(const struct matrix* mat, float scalar);

// Функция возвращает матрицу, в которой нет строки и столбца по номеру index
struct matrix minor(const struct matrix* mat, int n, int index);

// Функция, возвращающая определитель квадратной матрицы NxN
float matrixDeterm(const struct matrix* mat, int n);

// Функция, возвращающая транспонированную матрицу
struct matrix matrixTranspose(const struct matrix* mat);

// Функция, возвращающая экспоненту матрицы (N - кол-во членов ряда)
struct matrix matrixExponent(const struct matrix* mat, int N);

void matrixMalloc(struct matrix* mat, int rows, int cols)
{
    // Инициализируем кол-во строк и столбцов матрицы
    mat->_rows = rows;
    mat->_cols = cols;

    // Выделяем память для одномерного массива
    mat->_data = malloc(sizeof(void*) * rows * cols);
}

void matrixFree(struct matrix* mat)
{
    free(mat->_data);

    // Обнуляем кол-во строк и столбцов матрицы
    mat->_rows = 0;
    mat->_cols = 0;
}

void matrixPrint(const struct matrix* mat)
{
    for(int i = 0; i < mat->_rows; ++i)
    {
        // Выводим каждый элемент строки через пробел
        for(int j = 0; j < mat->_cols; ++j)
            printf("%f ", *matrixGetValue(mat, i, j));
        // Переход на новую строку
        printf("\n");
    }
}

float* matrixGetValue(const struct matrix* mat, int i, int j)
{
    return &mat->_data[j + i * mat->_rows];
}

struct matrix matrixSum(const struct matrix* mat1, const struct matrix* mat2)
{
    if(mat1->_rows != mat2->_rows || mat1->_cols != mat2->_cols)
    {
        printf("Кол-во строк и столбцов первой матрицы не равно кол-ву строк и столбцов второй матрицы!");
        exit(1);
    }

    // Создание матрицы результата сложения
    struct matrix result;
    matrixMalloc(&result, mat1->_rows, mat1->_cols);

    // Заполнения матрицы сложения
    for(int i = 0; i < mat1->_rows; ++i)
        for(int j = 0; j < mat1->_cols; ++j)
            *matrixGetValue(&result, i, j) = *matrixGetValue(mat1, i, j) + *matrixGetValue(mat2, i, j);

    // Возвращение результата сложения
    return result;
}

struct matrix matrixSubtract(const struct matrix* mat1, const struct matrix* mat2)
{
    if(mat1->_rows != mat2->_rows || mat1->_cols != mat2->_cols)
    {
        printf("Кол-во строк и столбцов первой матрицы не равно кол-ву строк и столбцов второй матрицы!");
        exit(1);
    }
    // Создание матрицы результата вычитания
    struct matrix result;
    matrixMalloc(&result, mat1->_rows, mat1->_cols);

    // Заполнения матрицы вычитания
    for(int i = 0; i < mat1->_rows; ++i)
        for(int j = 0; j < mat1->_cols; ++j)
            *matrixGetValue(&result, i, j) = *matrixGetValue(mat1, i, j) - *matrixGetValue(mat2, i, j);

    // Возвращение результата вычитания
    return result;
}

struct matrix matrixMultiply(const struct matrix* mat1, const struct matrix* mat2)
{
    if(mat1->_rows != mat2->_cols)
    {
        printf("Кол-во строк первой матрицы не равно кол-ву столбцов второй матрицы!");
        exit(1);
    }

    // Создание матрицы результата умножения
    struct matrix result;
    matrixMalloc(&result, mat1->_rows, mat2->_cols);

    // Заполнения матрицы умножения
    for(int i = 0; i < mat1->_rows; ++i)
        for(int j = 0; j < mat2->_cols; ++j)
        {
            // Инициализация всех значений нулём (чтобы не было сложения с мусором)
            *matrixGetValue(&result, i, j) = 0.0f;

            for(int k = 0; k < mat2->_rows; ++k)
                *matrixGetValue(&result, i, j) += *matrixGetValue(mat1, i, k) * *matrixGetValue(mat2, k, j);
        }

    // Возврат результата умножения
    return result;
}

struct matrix matrixMultiplyScalar(const struct matrix* mat, float scalar)
{
    // Создание матрицы результата скалярного умножения
    struct matrix result;
    matrixMalloc(&result, mat->_rows, mat->_cols);

    // Заполнения матрицы скалярного умножения
    for(int i = 0; i < mat->_rows; ++i)
        for(int j = 0; j < mat->_cols; ++j)
            *matrixGetValue(&result, i, j) = *matrixGetValue(mat, i, j) * scalar;

    // Возврат результата скалярного умножения
    return result;
}

struct matrix matrixDivideScalar(const struct matrix* mat, float scalar)
{
    // Создание матрицы результата деления матрицы на скаляр
    struct matrix result;
    matrixMalloc(&result, mat->_rows, mat->_cols);

    // Заполнения матрицы деления на скаляр
    for(int i = 0; i < mat->_rows; ++i)
        for(int j = 0; j < mat->_cols; ++j)
            *matrixGetValue(&result, i, j) = *matrixGetValue(mat, i, j) / scalar;

    // Возврат результата деления матрицы на скаляр
    return result;
}

struct matrix minor(const struct matrix* mat, int n, int index)
{
    // Создаем матрицу на 1 меньше mat (без строки и столка по номеру index)
    struct matrix res;
    matrixMalloc(&res, n - 1, n - 1);

    // Заполнение матрицы результата значениями текущей матрицы
    for (int i = 1; i < n; ++i)
        for (int j = 0, k = 0; j < n; ++j, ++k)
        {
            if (j == index)
            {
                --k;
                continue;
            }
            *matrixGetValue(&res, i - 1, k) = *matrixGetValue(mat, i, j);
        }

    // Возврат результата
    return res;
}

float matrixDeterm(const struct matrix* mat, int n)
{
    if(mat->_rows != mat->_cols)
    {
        printf("Кол-во строк матрицы не равно кол-ву столбцов!");
        exit(1);
    }
    // Определитель для матрицы 1x1
    if(n == 1)
        return *matrixGetValue(mat, 0, 0);
    // Определитель для матрицы 2x2
    if(n == 2)
        return (*matrixGetValue(mat, 1, 1) * *matrixGetValue(mat, 0, 0)) - (*matrixGetValue(mat, 0, 1) * *matrixGetValue(mat, 1, 0));
    // Определитель для матрицы 3x3 (метод треугольников)
    if(n == 3)
    {
        // Получаем первый треугольник
        float triangle_1 = *matrixGetValue(mat, 0, 0) * *matrixGetValue(mat, 1, 1) * *matrixGetValue(mat, 2, 2) +
                           *matrixGetValue(mat, 0, 1) * *matrixGetValue(mat, 1, 2) * *matrixGetValue(mat, 2, 0) +
                           *matrixGetValue(mat, 0, 2) * *matrixGetValue(mat, 1, 0) * *matrixGetValue(mat, 2, 1);
        // Получаем второй треугольник
        float triangle_2 = *matrixGetValue(mat, 0, 2) * *matrixGetValue(mat, 1, 1) * *matrixGetValue(mat, 2, 0) +
                           *matrixGetValue(mat, 0, 0) * *matrixGetValue(mat, 1, 2) * *matrixGetValue(mat, 2, 1) +
                           *matrixGetValue(mat, 0, 1) * *matrixGetValue(mat, 1, 0) * *matrixGetValue(mat, 2, 2);

        // Возврат определителя
        return triangle_1 - triangle_2;
    }

    // Если размерность матрицы больше 3, то вычисляется определитель матрицы NxN
    float determ = 0, minus = 1;
    for (int i = 0; i < n; ++i)
    {
        // Создание матрицы минора
        struct matrix min = minor(mat, n, i);

        determ += (minus * *matrixGetValue(mat, 0, i) * matrixDeterm(&min, n - 1));
        minus = -minus;

        // Удаление матрицы минора
        matrixFree(&min);
    }

    // Возврат определителя
    return determ;
}

struct matrix matrixTranspose(const struct matrix* mat)
{
    // Создание матрицы результата транспонирования
    struct matrix result;
    matrixMalloc(&result, mat->_cols, mat->_rows);

    // Заполнение транспонированной матрицы (строки и столбцы меняются местами)
    for(int i = 0; i < result._rows; ++i)
        for(int j = 0; j < result._cols; ++j)
            *matrixGetValue(&result, i, j) = *matrixGetValue(mat, j, i);

    // Возврат транспонированной матрицы
    return result;
}

struct matrix matrixExponent(const struct matrix* mat, int N)
{
    // Создание единичных квадратных матриц той же размерности, что и mat
    struct matrix e, t, temp, eCopy;
    matrixMalloc(&e, mat->_rows, mat->_rows);
    matrixMalloc(&t, mat->_rows, mat->_rows);

    for(int i = 0; i < mat->_rows; ++i)
    {
        *matrixGetValue(&e, i, i) = 1;
        *matrixGetValue(&t, i, i) = 1;
        for(int j = 0; j < mat->_cols; ++j)
        {
            if(i == j)
                continue;

            *matrixGetValue(&e, i, j) = 0;
            *matrixGetValue(&t, i, j) = 0;
        }
    }

    // Расчет матрицы экспоненты
    for(int i = 1; i <= N; ++i)
    {
        temp = matrixMultiply(&t, mat);
        matrixFree(&t);

        t = matrixDivideScalar(&temp, (float)i);
        matrixFree(&temp);

        eCopy = matrixSum(&e, &t);
        matrixFree(&e);
        e = eCopy;
    }

    // Возврат матрицы экспоненты
    return e;
}


int main(int argc, char* argv[])
{
    // русский язык в консоли
    system("chcp 65001");

    // Создание матриц
    struct matrix mat1;
    struct matrix mat2;
    struct matrix mat3;
    struct matrix mat4;

    // Матрицы для хранения результатов сложения, умножения и т.д.
    struct matrix matSum;
    struct matrix matSub;
    struct matrix matMul;
    struct matrix matMulScal;
    struct matrix matTrans;
    struct matrix matExp;

    matrixMalloc(&mat1, 3, 3);
    matrixMalloc(&mat2, 3, 3);
    matrixMalloc(&mat3, 4, 3);
    matrixMalloc(&mat4, 3, 4);

    // Заполнение матриц
    // mat1
    {
        *matrixGetValue(&mat1, 0, 0) = 4.0f;
        *matrixGetValue(&mat1, 0, 1) = 3.0f;
        *matrixGetValue(&mat1, 0, 2) = -7.0f;

        *matrixGetValue(&mat1, 1, 0) = -5.0f;
        *matrixGetValue(&mat1, 1, 1) = -6.0f;
        *matrixGetValue(&mat1, 1, 2) = 0.0f;

        *matrixGetValue(&mat1, 2, 0) = -1.0f;
        *matrixGetValue(&mat1, 2, 1) = 2.0f;
        *matrixGetValue(&mat1, 2, 2) = 3.0f;

    }
    // mat2
    {
        *matrixGetValue(&mat2, 0, 0) = 1.0f;
        *matrixGetValue(&mat2, 0, 1) = -2.0f;
        *matrixGetValue(&mat2, 0, 2) = -3.0f;

        *matrixGetValue(&mat2, 1, 0) = 3.0f;
        *matrixGetValue(&mat2, 1, 1) = -1.0f;
        *matrixGetValue(&mat2, 1, 2) = 9.0f;

        *matrixGetValue(&mat2, 2, 0)= -7.0f;
        *matrixGetValue(&mat2, 2, 1) = 6.0f;
        *matrixGetValue(&mat2, 2, 2) = 7.0f;

    }
    // mat3
    {
        *matrixGetValue(&mat3, 0, 0) = 4.0f;
        *matrixGetValue(&mat3, 0, 1) = 3.0f;
        *matrixGetValue(&mat3, 0, 2) = -7.0f;

        *matrixGetValue(&mat3, 1, 0) = -5.0f;
        *matrixGetValue(&mat3, 1, 1) = -6.0f;
        *matrixGetValue(&mat3, 1, 2) = 0.0f;

        *matrixGetValue(&mat3, 2, 0) = -1.0f;
        *matrixGetValue(&mat3, 2, 1) = 2.0f;
        *matrixGetValue(&mat3, 2, 2) = 3.0f;

        *matrixGetValue(&mat3, 3, 0) = -9.0f;
        *matrixGetValue(&mat3, 3, 1) = -6.0f;
        *matrixGetValue(&mat3, 3, 2) = 7.0f;

    }
    // mat4
    {
        *matrixGetValue(&mat4, 0, 0) = 1.0f;
        *matrixGetValue(&mat4, 0, 1) = 5.0f;
        *matrixGetValue(&mat4, 0, 2) = -1.0f;
        *matrixGetValue(&mat4, 0, 3) = 2.0f;

        *matrixGetValue(&mat4, 1, 0) = 4.0f;
        *matrixGetValue(&mat4, 1, 1) = 3.0f;
        *matrixGetValue(&mat4, 1, 2) = -1.0f;
        *matrixGetValue(&mat4, 1, 3) = 2.0f;

        *matrixGetValue(&mat4, 2, 0)= -3.0f;
        *matrixGetValue(&mat4, 2, 1) = 4.0f;
        *matrixGetValue(&mat4, 2, 2) = 4.0f;
        *matrixGetValue(&mat4, 2, 3) = -1.0f;


    }

    // Вывод изначальных матриц
    printf("Матрица mat1: \n");
    matrixPrint(&mat1);
    printf("Матрица mat2: \n");
    matrixPrint(&mat2);
    printf("Матрица mat3: \n");
    matrixPrint(&mat3);
    printf("Матрица mat4: \n");
    matrixPrint(&mat4);

    // Тестирование операций над матрицами
    printf("Определитель матрицы mat1 = %f\n", matrixDeterm(&mat1, mat1._rows));
    printf("Определитель матрицы mat2 = %f\n", matrixDeterm(&mat2, mat2._rows));
    printf("\n");

    printf("Сложение матриц mat1 и mat2: \n");
    matSum = matrixSum(&mat1, &mat2);
    matrixPrint(&matSum);
    printf("\n\n");

    printf("Вычитание матриц mat1 и mat2: \n");
    matSub = matrixSubtract(&mat1, &mat2);
    matrixPrint(&matSub);
    printf("\n\n");

    printf("Умножение матриц mat3 и mat4: \n");
    matMul = matrixMultiply(&mat3, &mat4);
    matrixPrint(&matMul);
    printf("\n\n");

    printf("Умножение матрицы mat1 на число 10: \n");
    matMulScal = matrixMultiplyScalar(&mat1, 10.0f);
    matrixPrint(&matMulScal);
    printf("\n\n");

    printf("Транспонирование матрицы mat4: \n");
    matTrans = matrixTranspose(&mat4);
    matrixPrint(&matTrans);
    printf("\n\n");

    printf("Матрица-экспонента матрицы mat1, где N = 10: \n");
    matExp = matrixExponent(&mat1, 10);
    matrixPrint(&matExp);
    printf("\n\n");

    // Удаление матриц
    matrixFree(&mat1);
    matrixFree(&mat2);
    matrixFree(&mat3);
    matrixFree(&mat4);
    matrixFree(&matSum);
    matrixFree(&matSub);
    matrixFree(&matMul);
    matrixFree(&matMulScal);
    matrixFree(&matExp);

    return 0;
}
