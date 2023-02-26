#include <iostream>

// Тут можно указать любой тип элементов матрицы
typedef float mat_type;

// Класс матрицы
class Matrix
{
public:
    // Конструкторы
    Matrix(int rows, int cols);
    Matrix(int rows);
    Matrix();
    // Конструктор копирования
    Matrix(const Matrix& mat);
    // Деструктор
    ~Matrix();

    // Перегруженный оператор вывода матрицы на консоль
    friend std::ostream& operator << (std::ostream& stream, const Matrix& mat);

    // Перегруженный оператор присваивания
    Matrix& operator = (const Matrix& mat);
    // Перегруженный оператор сложения матриц
    Matrix operator + (const Matrix& mat) const;
    // Перегруженный оператор вычитания матриц
    Matrix operator - (const Matrix& mat) const;
    // Перегруженный оператор умножения матриц
    Matrix operator * (const Matrix& mat) const;
    // Перегруженный оператор умножения матрицы на число
    Matrix operator * (mat_type scalar) const;
    // Перегруженный оператор деления матрицы на число
    Matrix operator / (mat_type scalar) const;

    // Возвращает матрицу без index строки и столбца
    Matrix minor(int n, int index) const;

    // Возвращает определитель матрицы
    mat_type determ(int n) const;

    // Возвращает транспонированную матрицу
    Matrix transpose() const;

    // Возвращает матрицу-экспоненту текущей матрицы
    Matrix exponent(int N) const;

    // Методы-геттеры
    int getRows() const;
    int getCols() const;
    mat_type& getValue(int i, int j) const;
private:
    // Значения матрицы
    mat_type** _mat;
    // Кол-во строк и столбцов матрицы
    int _rows;
    int _cols;
};
