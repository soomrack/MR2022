
#ifndef MATRIX_CAL_MATRIX_H  // для того чтобы не было залипания библиотек на бесконечность их подключения
#define MATRIX_CAL_MATRIX_H  // для того чтобы не было залипания библиотек на бесконечность их подключения
#include <math.h>            // подключение математики
#include <stdio.h>           // подключение стандартной библиотеки ввода и вывода
#include <stdlib.h>          // подключение ради ф малок


const double EPS = 10e-6;    // епселанд для сравнения чисел с плав точкой

typedef struct Matrix{       // объявление структуры и ниже создание ее 3 аргументов
    unsigned int rows;       // только положительные - строки
    unsigned int cols;       // столбцы
    double* values;          // дабл+звездочка - это указатель на дабл (указатель велью, то есть где он находится в ЭВМ)

} Matrix;                    // чтобы не прописывать везде struct, а просто сразу писать имя структуры = Matrix


void printm(struct Matrix mat){  // Создание функции вывода матрицы в консоль 1) тип данных - void(пустота)=без возврата(без return) 2) название функции(тип данных аргумента(struct Matrix) и аргумент(mat) и 3) тело функции в фигурных скобках
    printf("\n");                                            // переход на новую строчку
    for (unsigned int row = 0; row < mat.rows; row++){              // пробежка по элементам строки
        for (unsigned int col = 0; col < mat.cols; col++){          // пробежка по элементам столбца
            printf(" %f", mat.values[row * mat.cols + col]);  // вывод каждого элемента матрицы
        }
        printf("\n");                                         // перевод на новую строку
    }
}


Matrix create_null(){ // создание функции которую вызывают во время исключительных событий по ходу программы (например число строк 1 = число строк 2, если ее нет то наша программа выводит НУЛЛ матрицу, которую создали)
    Matrix mat = {0, 0, NULL};
    return mat;
}


Matrix create_empty(const unsigned int rows, const unsigned int cols){  // Создание функции пустой не заполненной матрицы где не изменяем столбцы и строки

    double* data_ptr = malloc(sizeof(double) * rows * cols);        // data_ptr - дата поинтер (указатель и сущ только в этой функции) хранит адрес первого элемента массива который выделяет ОС
                                                                         // в оперативной памяти + выделение памяти функцией malloc на кол-во элементов матрицы = строки*столбцы

    if (data_ptr == NULL) return create_null();                          // если дата поинтер = 0 то возвращаемся к create_null, нужна если ОС не выделит память
    Matrix mat = {rows, cols, data_ptr};                           // если все ОК то создаем матрицу из столбцы, строки, указатель на 1 элемент массива (сам массив)
    return mat; // возврат матрицы
}


Matrix create_zero(const unsigned int rows, const unsigned int cols){  // Создание функции НУЛЕВОЙ матрицы для последующей математической работы
    Matrix mat = create_empty(rows, cols); // создаем матрицу мат - новой пустой патрицы предыдущей функции create_empty с выделением памяти и ее контролированием
    for (unsigned int idx = 0; idx < rows * cols; idx++) mat.values[idx] = 0.0; // Эта строчка делает все эл матрицы 0 // цикл индекс (idx) = номер элемента в массиве если индекс меньше количества эл в матрице то прибавляем 1 ПОСЛЕ матрица которую создали обращаемся к ее велью (указателю) и приравниваем к 0.
    return mat;
}



Matrix create_identity(const unsigned int size){    // Создание функции единичной матрицы (на главной диагонали 1 а в других 0), сайз потому что она квадратная и строки=стобцы
    Matrix mat = create_zero(size, size);
    for (unsigned int idx = 0; idx < size * size; idx += size + 1){  // пробежка по элементам матрицы
        mat.values[idx] = 1.0;                                       // подставляем 1 в диагональные элементы
    }
    return mat;
}



Matrix create_random(const unsigned int rows, const unsigned int cols, const double max_value){ // Создание функции для матрицы со случайными значениями
    Matrix mat = create_empty(rows, cols);
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        mat.values[idx] = ((double)rand() / (double)(RAND_MAX)) * max_value;
    }
    return mat;
}



void set_to_identity(Matrix* mat){ // Функция создания ед матрицы
    if (mat->cols != mat->rows) { // проверка на квадратную матрицу
        mat->rows = 0;
        mat->cols = 0;
        mat->values = NULL;
    }
    unsigned int size = mat->cols;
    for (unsigned int idx = 0; idx < size * size; idx++){
        mat->values[idx] = idx % (size + 1) == 0 ? 1.0 : 0.0; // тернарный оператор чтобы записать по условию или 0 или 1 // указатель процент от деления если остаток от деления равен 0 то пишем 1 если нет то пишем 0
    }
}



Matrix copy(const Matrix mat){  // Функция создания копии матрицы
    Matrix copy = create_empty(mat.rows, mat.cols);
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++) copy.values[idx] = mat.values[idx];
    return copy;
}



int is_equal(const Matrix mat1, const Matrix mat2){  // Проверяет равны ли две матрицы
    if (mat1.cols != mat2.cols || mat1.rows != mat2.rows) return 0; // проверка на размерность матриц если разные то возвращаем 0 ложь
    for (unsigned int idx = 0; idx < mat1.cols * mat1.rows; idx++){
        if (fabs(mat1.values[idx] - mat2.values[idx]) > EPS) return 0; // fabs встроенный модуль для чисел с плавающей точкой и если этот модуль от разности больше чем ЭПСЕЛЕНД то возвращаем 0 - ложь
    }
    return 1; // возврат 1 - правда если не прерывался цикл ранее на ретерне 0
}


int is_identity(const Matrix matrix){ // проверка матрицы на то явл ли она единичной
    if (matrix.cols != matrix.rows) return 0; // ведь ед матрица всегда квадратная
    unsigned int size = matrix.rows;
    for (unsigned int idx = 0; idx < size * size; idx++){
        if (idx % (size + 1) == 0){
            if (fabs(matrix.values[idx] - 1) > EPS)  return 0; // сравнение на главное диаганали с 1 // СПОСОБ для сравнения чисел с плав точкой
        }
        else{
            if (fabs(matrix.values[idx] - 0) > EPS) return 0; // сравнение с остальными на 0 (явля ли они 0)
        }
    }
    return 1; // - вывод тру
}



Matrix add(Matrix m1, const Matrix m2){  // Сложение двух матриц
    if (m1.cols != m2.cols || m1.rows != m2.rows){   // || - обозанчает или
        return create_null(); // возврат 0 если они не размерны
    }
    for (unsigned int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] + m2.values[idx]; // сложение по элементов
    }
    return m1; // m1.values[idx] запись результата и вовзрат матрицы 1
}



Matrix sub(Matrix m1, const Matrix m2){  // Вычитание двух матриц
    if (m1.cols != m2.cols || m1.rows != m2.rows){
        return create_null();
    }
    for (unsigned int idx = 0; idx < m1.rows * m1.cols; idx++){
        m1.values[idx] = m1.values[idx] - m2.values[idx];
    }
    return m1;
}



Matrix mul(Matrix m1, const Matrix m2){  // Умножение двух матриц
    if (m1.cols != m2.rows){
        return create_null();
    }
    Matrix temp = create_empty(m1.rows, m1.cols); // создание временной матрицы
    for (unsigned int row = 0; row < temp.rows; row++){     // проходимся по всем строкам
        for (unsigned int col = 0; col < temp.cols; col++){   // по всем столбца
            double summa = 0.0; // временная переменная = 0 после этого доб счетчика ниже
            for (unsigned int idx = 0; idx < m1.cols; idx++){    //
                summa += m1.values[row * m1.cols + idx] * m2.values[idx * m2.cols + col];
            }
            temp.values[temp.cols * row + col] = summa;
        }
    }
    free(m1.values); // освобождение памяти от м1 тк мы ее поменяли
    m1.values = temp.values; // указатель м1 поменяли на указатель темп
    return m1;
}



Matrix s_mul(const Matrix mat, const double scal){  // Умножение матрицы на скаляр
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] * scal;
    }
    return mat;
}



Matrix s_div(const Matrix mat, const double scal){  // Деление матрицы на скаляр
    for (unsigned int idx = 0; idx < mat.rows * mat.cols; idx++){
        mat.values[idx] = mat.values[idx] / scal;
    }
    return mat;
}



Matrix transpose(Matrix mat){  // Транспонирование матрицы
    Matrix temp = create_empty(mat.cols, mat.rows);
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            temp.values[col * temp.rows + row] = mat.values[row * temp.cols + col];
        }
    }
    free(mat.values);
    mat = temp;
    return mat;
}



Matrix minor(Matrix mat, const unsigned int minor_row, const unsigned int minor_col){  // Минор матрицы по строке minor_row и столбцу minor_col
    Matrix temp = create_empty(mat.rows - 1, mat.cols - 1);
    int minor_index = 0;
    for (unsigned int row = 0; row < mat.rows; row++){            // прохождение по матрице
        for (unsigned int col = 0; col < mat.cols; col++) {       // прохождение по матрице
            if (row != minor_row && col != minor_col) {           //
                temp.values[minor_index++] = mat.values[row * mat.rows + col];
            }
        }
    }
    free(mat.values);
    mat = temp;
    return mat;
}



double m_det(const Matrix mat){  // Рекурсивная функция определителя матрицы
    if (mat.cols != mat.rows){
        return NAN;
    }
    double ans = 0.0; // ансер = определитель
    if (mat.rows == 2){ // == это сравнение
        ans = mat.values[0] * mat.values[3] - mat.values[1] * mat.values[2];  // определитель 2 на 2 главная и побочная диагональ
        return ans;
    }  // Определитель матрицы порядка 2 считается по формуле
    for (unsigned int idx = 0; idx < mat.rows; idx++){ // пробег по всем строкам
        if (mat.values[idx] != 0){
            Matrix temp = minor(copy(mat), 0, idx);
            ans += mat.values[idx] * pow(-1, idx) * m_det(temp); // формула развернутая для определителя матрицы
            free(temp.values); // освобождаем память от временной матрицы
        }
    }  // Определители матриц больших порядков считаются разложением по первой строке
    return ans; // показать определить
}



double m_tr(Matrix mat){  // След (trace) матрицы это сумма элементов главной диагонали
    if (mat.cols != mat.rows){
        return NAN;
    }
    unsigned int size = mat.cols;
    double trace = 0.0;
    for (unsigned int idx = 0; idx < size * size; idx += size + 1) trace += mat.values[idx];
    return trace;
}



Matrix m_inv(Matrix mat){  // Обратная матрица
    if (mat.cols != mat.rows){
        return create_null();
    }
    Matrix ans = create_empty(mat.rows, mat.cols);
    double determinant = m_det(mat);
    Matrix temp;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            temp = minor(copy(mat), row, col);
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
                                               m_det(temp) / determinant;
        }
    }
    free(mat.values);
    free(temp.values);
    mat = ans;
    return mat;
}


void iterate_exp(const Matrix* ans, const Matrix mat){  //функция описывает вычисление матричной экспоненты в произвольной матрице (более сложный вариант)

    unsigned int max_cycles = 100; // не больше 100 циклов - условия выхода из цикла

    Matrix power = mat; // временная переменная в которой мы храним степень матрицы
    unsigned long long int factorial = 1; // факториал временная переменная первоначально присваиваем 1
    Matrix temp = create_identity(ans->rows); // временная матрица в которой будет хранить наш ответ и делаем ее единичной
    int counter = 1; // временная переменная для 1) счетчика отсчитывания кол-ва циклов и сравниваем ее с максимальный 100 кол-вом 2) для определения факториала
    while (counter < max_cycles){      // выполняется пока счетчик менее 100 по условию
        temp = add(temp, s_div(power, (double) factorial));  //
        factorial *= ++counter; // счетчик увеличивается на 1 а затем умножается на факториал
        power = mul(power, mat); // степень матрицы становится перемножением степени на матрицу для перехода из низшей степение в высшую (например из 3 в 4) // повышение степени
    }
    for (unsigned int idx = 0; idx < ans->rows * ans->cols; idx++) ans->values[idx] = temp.values[idx]; // копируем матрицы из временной в матрицу ответ
    free(temp.values);
    free(power.values);
}



Matrix m_exp(Matrix mat){  // Матричная экспонента для матрицы диагонального вида (по формуле каждый НЕ 0 элемент(по диагонали) возводим в экспоненту
    if (mat.cols != mat.rows) return create_null();
    Matrix ans = create_empty(mat.rows, mat.cols);
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            if (row != col){
                if (fabs(mat.values[row * mat.cols + col]) > EPS){
                    iterate_exp(&ans, mat);
                    return ans;
                }
                else ans.values[row * mat.cols + col] = 0;
            }
            else ans.values[row * mat.cols + col] = exp(mat.values[row * mat.cols + col]);
        }
    }
    return ans;
}
#endif //MATRIX_CAL_MATRIX_H
