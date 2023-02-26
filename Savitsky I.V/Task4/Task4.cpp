#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <stdlib.h>

const double EPS = 0.000001;

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};

Matrix_Exception NOT_SQUARE("Make matrix square\n");
Matrix_Exception SIZE_ERROR("Change a size\n");
Matrix_Exception DIVISION_ERROR("Can't divide by zero\n");

template<typename T>
class Matrix {
protected:
    unsigned int cols;
    unsigned int rows;
    T* values;

public:

    static_assert(
        std::is_same<double, T>::value ||
        std::is_same<float, T>::value ||
        std::is_same<long double, T>::value ||
        "T could be double, float or long double");
    Matrix();  // Пустая матрица
    Matrix(unsigned int col, unsigned int row);  // Прямоугольная матрица
    Matrix(unsigned int col);  // Единичная матрица
    Matrix(const Matrix& matrix);  // Копирование матрицы
    Matrix(Matrix&& matrix);  // Перенос матрицы
   ~Matrix();  // Деструктор


    void output();
    void set_rand_values(const unsigned int max_value);

    Matrix operator+(const Matrix<T>&);
    Matrix operator-(const Matrix<T>&);
    Matrix operator*(const Matrix<T>&);
    Matrix operator*(const T);
    Matrix operator=(Matrix<T>&);
    Matrix operator=(Matrix<T>&&);
    Matrix operator^(const T) const;
    Matrix operator/(const T) const;
    static Matrix  exp(const Matrix<T>&, const unsigned int accuracy);
    Matrix Minor(Matrix<T>&, const unsigned int row, const unsigned int col);
    Matrix transpose();
    double determinant(const Matrix<T>&);

    friend std::ostream& operator<<(std::ostream& out, Matrix<T> matrix)
    {
        {
            for (unsigned int row = 0; row < matrix.rows; row++)
            {
                for (unsigned int col = 0; col < matrix.cols; col++)
                {
                    out << matrix.values[row * matrix.cols + col] << "\t";
                }
                out << std::endl;
            }
            out << std::endl;
            return(out);
        }
    }
};


template <typename T>
Matrix<T>::Matrix() {
    cols = 0;
    rows = 0;
}

template <typename T>
Matrix<T>::~Matrix()
{
    if (values != nullptr) {
        delete[] values;
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new T[cols * rows];
   
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new T[rows * cols];
    memcpy(values, matrix.values, rows * cols * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
}

template <typename T>
void Matrix<T>::output() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
void Matrix<T>::set_rand_values(const unsigned int max) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = rand()%max;
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    values = new T[cols * rows];
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1 : 0;

        }
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& One) {
    if (rows != One.rows) throw SIZE_ERROR;
    Matrix res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        res.values[idx] += values[idx];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& One) {
    if (rows != One.rows) throw SIZE_ERROR;
    Matrix Res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] -= values[idx];
    }
    return Res;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& One) {
    if (rows != One.rows) throw SIZE_ERROR;
    Matrix Res(One);
    for (unsigned int row = 0; row < Res.rows; row++) {
        for (unsigned int col = 0; col < Res.cols; col++) {
            Res.values[row * Res.rows + col] = 0.00;
            for (unsigned int k = 0; k < Res.cols; k++) {
                Res.values[row * Res.cols + col] += values[row * cols + k] * One.values[k * Res.cols + col];
            }
        }
    }
    return Res;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T coefficient) {
    Matrix Res(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        Res.values[idx] = values[idx] * coefficient;
    }
    return Res;
}


template <typename T>
Matrix<T> Matrix<T>::operator= (Matrix<T>& one) {
    if (this == &one) {
        return *this;
    }
    rows = one.rows;
    cols = one.cols;
    delete[]values;
    values = new T[cols * rows];
    memcpy(values, one.values, rows * cols * sizeof(double));
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator= (Matrix<T>&& one) {
    if (this == &one) {
        return *this;
    }
    rows = one.rows;
    cols = one.cols;
    delete[]values;
    values = one.values;
    one.values = nullptr;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator^(const T coefficient) const {
    if (cols != rows) throw NOT_SQUARE;
    Matrix Res(*this);
    if (coefficient == 0) {
        Matrix one(cols);
        return one;
    }
    if (coefficient == 1) {
        return Res;
    }
    else {
        const Matrix& start(Res);
        for (unsigned int idx = 0; idx < coefficient; idx++) {
            Res = Res * start;
        }
        return Res;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T coefficient) const {
    Matrix Res(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; ++idx) {
        Res.values[idx] = values[idx] / coefficient;
    }
    return Res;
}


template <typename T>
Matrix<T> Matrix<T>::exp(const Matrix<T>& A, const unsigned int accuracy) {
    if (A.rows != A.cols) throw NOT_SQUARE;
    Matrix one(A.cols);
    Matrix Res = one + A;
    double factorial = 1;
    for (int step = 1; step < accuracy; step++) {
        factorial *= step;
        Res = Res + (A ^ step) / factorial;
    }
    return Res;
}

template <typename T>
Matrix<T> Matrix<T>::Minor(Matrix<T>& A, unsigned int row, unsigned int col) {
    int new_row = A.rows - 1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix Res = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if ((idx % cols == col) or (idx / cols == row)) continue;
        Res.values[k++] = A.values[idx];
    }

    return Res;
}
template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix res = { cols, rows };
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = values[col * res.cols + row];
        }
    }
    return res;
}

template <typename T>
double Matrix<T>::determinant(const Matrix<T>& matrix)
{
    if (cols != rows) throw NOT_SQUARE;
    double det = 0;
    int sign = 1;
    if (rows == 0 and cols == 0)
        return 0;
    if (rows == 1 and cols == 1)
        return matrix.values[0];
    if (rows == 2 and cols == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < rows; idx++) {
        det += sign * matrix.values[idx] * determinant(Minor(matrix, 0, idx), rows - 1);
        sign = -sign;
    }
    return det;
}


template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
    static unsigned long memory_size;
    static unsigned long total_memory;
public:
    Matrix_Memory<T1>();
    Matrix_Memory<T1>(unsigned int, unsigned int);
    Matrix_Memory<T1>(const Matrix_Memory<T1>&);
    Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
    ~Matrix_Memory();
    Matrix_Memory<T1>& operator= (const  Matrix_Memory<T1>&);
    void report();
};

template <typename T>
Matrix_Memory<T>& ::Matrix_Memory<T>::operator=(const Matrix_Memory<T>& matrix) {
    if (this == &matrix)
    {
        return *this;
    }
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[] this->values;
    this->values = new T[this->cols * this->rows];
    memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));
    memory_size += matrix.memory_size;
    total_memory += memory_size;
    return *this;
}

template <typename T>
Matrix_Memory<T>::Matrix_Memory()
{
    this->memory_size += 0;
    this->total_memory += 0;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col)
{
    this->rows = row;
    this->cols = col;
    this->values = new T[this->rows * this->cols];
    memory_size = row * col * sizeof(T);
    total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::~Matrix_Memory()
{
    total_memory -= memory_size;
}
template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& matrix)
{
    this->values = new T[this->rows * this->cols];
    memcpy(this->values, matrix.values, sizeof(T) * this->rows * this->cols);
    memory_size = matrix.memory_size;
    total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& matrix) noexcept
{

    memory_size = matrix.memory_size;

    matrix.rows = 0;
    matrix.cols = 0;
    matrix.values = nullptr;
    matrix.memory_size = 0;
}


template <typename T>
void Matrix_Memory<T>::report()
{
    std::cout << "Total memory " << this->total_memory << " byte" << std::endl;
}

template <typename T>
unsigned long int Matrix_Memory<T>::total_memory = 0;
template <typename T>
unsigned long int Matrix_Memory<T>::memory_size = 0;

void main() {
    Matrix_Memory<float> matrix1(3, 3);
    matrix1.set_rand_values(10);
    std::cout << "Matrix 1\n";
    matrix1.output();
    Matrix_Memory<float> matrix2(3, 3);
    matrix2.set_rand_values(10);
    std::cout << "Matrix 2\n";
    matrix2.output();
    std::cout <<"Sum\n" << matrix1 + matrix2;
    std::cout << "Dif\n" << matrix1 - matrix2;
    std::cout << "Mult\n" << matrix1 * matrix2;
    std::cout << "Mult_k\n" << matrix1 * 3;
    std::cout <<"Div\n" << matrix1 / 3;
    std::cout <<"Exp\n" << matrix1.exp(matrix1, 3);
}