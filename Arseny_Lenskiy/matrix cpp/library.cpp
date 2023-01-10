#include "library.h"

Matrix::Matrix(int rows, int cols)
{
    _rows = rows;
    _cols = cols;

    _mat = new mat_type*[rows];
    for (int i = 0; i < rows; ++i)
        _mat[i] = new mat_type[cols];
}
Matrix::Matrix(int rows) : Matrix(rows, rows) {}
Matrix::Matrix()
{
    _rows = 0;
    _cols = 0;
    _mat = 0;
}
Matrix::Matrix(const Matrix& mat)
{
    _rows = mat._rows;
    _cols = mat._cols;

    // Инициализация и копирование элементов другой матрицы в текущую матрицу
    _mat = new mat_type * [mat._rows];
    for (int i = 0; i < mat._rows; ++i)
    {
        _mat[i] = new mat_type[mat._cols];

        for (int j = 0; j < mat._cols; ++j)
            _mat[i][j] = mat._mat[i][j];
    }
}
Matrix::~Matrix()
{
    if (_mat)
    {
        for (int i = 0; i < _rows; ++i)
            delete[] _mat[i];
        delete[] _mat;

        _rows = 0;
        _cols = 0;
    }
}

std::ostream& operator << (std::ostream& stream, const Matrix& mat)
{
    for (int i = 0; i < mat._rows; ++i)
    {
        // Вывод каждой строки чисел матрицы через пробел
        for (int j = 0; j < mat._cols; ++j)
            stream << mat._mat[i][j] << ' ';
        // Переход на новую строку
        stream << std::endl;
    }

    return stream;
}

Matrix& Matrix::operator = (const Matrix& mat)
{
    // Если текущая матрица не пустая, то удаляем её перед присваиванием
    if (_mat)
    {
        for (int i = 0; i < _rows; ++i)
            delete[] _mat[i];
        delete[] _mat;
    }

    _rows = mat._rows;
    _cols = mat._cols;

    // Инициализация и копирование элементов другой матрицы в текущую матрицу
    _mat = new mat_type * [mat._rows];
    for (int i = 0; i < mat._rows; ++i)
    {
        _mat[i] = new mat_type[mat._cols];

        for (int j = 0; j < mat._cols; ++j)
            _mat[i][j] = mat._mat[i][j];
    }

    // Возвращаем адрес текущей матрицы
    return *this;
}

Matrix Matrix::operator + (const Matrix& mat) const
{
    // Если кол-во строк или столбцов первой матрицы не равно кол-ву того же другой матрицы, то возвращает пустую матрицу
    if (_rows != mat._rows || _cols != mat._cols)
        return Matrix();

    // Создание результата сложения матриц
    Matrix result(_rows, _cols);

    // Заполнение результата сложения матриц
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            result._mat[i][j] = _mat[i][j] + mat._mat[i][j];

    // Возврат результата сложения
    return result;
}

Matrix Matrix::operator - (const Matrix& mat) const
{
    // Если кол-во строк или столбцов первой матрицы не равно кол-ву того же другой матрицы, то возвращает пустую матрицу
    if (_rows != mat._rows || _cols != mat._cols)
        return Matrix();

    // Создание результата вычитания матриц
    Matrix result(_rows, _cols);

    // Заполнение результата вычитания матриц
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            result._mat[i][j] = _mat[i][j] - mat._mat[i][j];

    // Возврат результата вычитания
    return result;
}

Matrix Matrix::operator * (const Matrix& mat) const
{
    // Если кол-во строк первой матрицы не равно кол-ву столбцов другой матрицы, то возвращаем нулевую матрицу
    if (_rows != mat._cols)
        return Matrix();

    // Создание матрицы результата умножения
    Matrix result(_rows, mat._cols);

    // Заполнения матрицы умножения
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < mat._cols; ++j)
        {
            // Инициализация всех значений нулём (чтобы не было сложения с мусором)
            result._mat[i][j] = 0;

            for (int k = 0; k < mat._rows; ++k)
                result._mat[i][j] += _mat[i][k] * mat._mat[k][j];
        }

    // Возврат результата умножения
    return result;
}

Matrix Matrix::operator * (mat_type scalar) const
{
    // Создание матрицы результата умножения
    Matrix result(_rows, _cols);

    // Заполнения матрицы умножения
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            result._mat[i][j] = _mat[i][j] * scalar;

    // Возврат результата умножения
    return result;
}

Matrix Matrix::operator / (mat_type scalar) const
{
    // Создание матрицы результата умножения
    Matrix result(_rows, _cols);

    // Заполнения матрицы умножения
    for (int i = 0; i < _rows; ++i)
        for (int j = 0; j < _cols; ++j)
            result._mat[i][j] = _mat[i][j] / scalar;

    // Возврат результата умножения
    return result;
}

Matrix Matrix::minor(int n, int index) const
{
    // Создаем матрицу на 1 меньше mat (без строки и столбца по номеру index)
    Matrix res(n - 1, n - 1);

    // Заполнение матрицы результата значениями текущей матрицы
    for (int i = 1; i < n; ++i)
        for (int j = 0, k = 0; j < n; ++j, ++k)
        {
            if (j == index)
            {
                --k;
                continue;
            }
            res._mat[i - 1][k] = _mat[i][j];
        }

    // Возврат результата
    return res;
}

mat_type Matrix::determ(int n) const
{
    if (_rows != _cols)
        return 0;

    // Определитель для матрицы 1x1
    if (n == 1)
        return _mat[0][0];
    // Определитель для матрицы 2x2
    if (n == 2)
        return (_mat[1][1] * _mat[0][0]) - (_mat[0][1] * _mat[1][0]);
    // Определитель для матрицы 3x3 (метод треугольников)
    if (n == 3)
    {
        // Получаем первый треугольник
        mat_type triangle_1 = _mat[0][0] * _mat[1][1] * _mat[2][2] +
                              _mat[0][1] * _mat[1][2] * _mat[2][0] +
                              _mat[0][2] * _mat[1][0] * _mat[2][1];
        // Получаем второй треугольник
        mat_type triangle_2 = _mat[0][2] * _mat[1][1] * _mat[2][0] +
                              _mat[0][0] * _mat[1][2] * _mat[2][1] +
                              _mat[0][1] * _mat[1][0] * _mat[2][2];

        // Возврат определителя
        return triangle_1 - triangle_2;
    }

    // Если размерность матрицы больше 3, то вычисляется определитель матрицы NxN
    mat_type determ = 0;
    short int minus = 1;
    for (int i = 0; i < n; ++i)
    {
        // Создание матрицы минора
        Matrix min = minor(n, i);

        determ += (minus * _mat[0][i] * min.determ(n - 1));
        minus = -minus;
    }

    // Возврат определителя
    return determ;
}

Matrix Matrix::transpose() const
{
    // Создание матрицы результата транспонирования
    Matrix result(_cols, _rows);

    // Заполнение матрицы транспонирования (строки и столбцы поменяны местами)
    for (int i = 0; i < result._rows; ++i)
        for (int j = 0; j < result._cols; ++j)
            result._mat[i][j] = _mat[j][i];

    // Возврат результата транспонирования
    return result;
}

Matrix Matrix::exponent(int N) const
{
    // Создание единичных квадратных матриц той же размерности, что и mat
    Matrix e(_rows, _rows), t(_rows, _rows);

    for (int i = 0; i < _rows; ++i)
    {
        e._mat[i][i] = 1;
        t._mat[i][i] = 1;
        for (int j = 0; j < _cols; ++j)
        {
            if (i == j)
                continue;

            e._mat[i][j] = 0;
            t._mat[i][j] = 0;
        }
    }

    // Расчет матрицы экспоненты
    for (int i = 1; i <= N; ++i)
    {
        t = (t * *this) / i;
        e = e + t;
    }

    // Возврат матрицы экспоненты
    return e;
}

int Matrix::getRows() const { return _rows; }
int Matrix::getCols() const { return _cols; }
mat_type& Matrix::getValue(int i, int j) const { return _mat[i][j]; };