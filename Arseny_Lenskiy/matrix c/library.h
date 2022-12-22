#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H
#include "malloc.h"
#include <stdio.h>
#include "math.h"

//Структура матриц

typedef // Чтобы не писать каждый раз обращение к структуре просто будем писать "Matrix"
struct Matrix{
    unsigned int cols;
    unsigned int rows;
    double* values; // Ссылки на значения
    double** item; // Ссылки на ссылки
} Matrix;

Matrix EMPTY = {0, 0, NULL, NULL};  // В случае ошибки вернуть нулевую матрицу

enum Message {ERR = 0, ADD = 1, SUB = 2, MULT = 3, DET = 4, EX = 5}; // Сообщения на выводе
char *MESSAGES[6] = {"\nIncompatible matrix sizes!\n","\nAddition\n",
                     "\nSubtraction\n","\nMultiplication\n",
                     "\nDeterminant\n","\nExponent\n"};

const double DETERMINANT_ACCURACY = 0.000001; // Точность определителя
const double EXPONENT_ACCURACY = 0.001; // Точность экспоненты
const int EXPONENT_STEPS = 100; // Количество повторов цикла экспоненты

// Создание матриц

Matrix create_zero_matrix(unsigned int rows, unsigned int cols); // Выделяем память под 0 матрицу
Matrix create_one_matrix(unsigned int rows, unsigned int cols); // Выделяем память под матрицу с 1 по диагонали
void fill_mat_summ(Matrix *matrix); //заполняем матрицу с помощью сложения номера строки и столбца
void fill_mat_mult(Matrix *matrix); // Заполняем матрицу с помощью умножения номеров строки и столбца
void fill_matrix_val(Matrix *matrix, const double* value); //Заполняем матрицу нашими значениями

// Действия с матрицами

Matrix matrix_add(Matrix fst_matx, Matrix snd_matx); // Сложение
Matrix matrix_subt(Matrix fst_matx, Matrix snd_matx); // Вычитание
Matrix matrix_mult(Matrix fst_matx, Matrix snd_matx); // Умножение
Matrix matrix_mult_by_num(double a, Matrix matrix); // Умножение на число
Matrix matrix_copy(Matrix matrix); // Копия
void change_rows(Matrix *matrix, int fst_row, int snd_row); // Замена строк
double matrix_det(Matrix matrix); //Подсчет детерминанта
double check_max_dif(Matrix fst_mat, Matrix snd_mat); // Разность между элементами двух массивов после каждой итерации
Matrix matrix_exp(Matrix matrix); // Подсчет матричной экспоненты
void free_mat(Matrix *matrix); // Освобождаем память которую занимала матрица
void message(int ind); // Функция которая выводит сообщения

// Проверка на двойной вызов библиотек

#endif //MATRIX_MATRIX_H
