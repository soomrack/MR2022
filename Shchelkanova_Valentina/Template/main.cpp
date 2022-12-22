#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <cstring>



template<typename T>
class Matrix {
protected:
    unsigned int cols;
    unsigned int rows;
    T *values;

public:

    static_assert(
            std::is_same<double, T>::value ||
            std::is_same<float,T>::value ||
            std::is_same<long double,T>::value ||
            "T could be double, float or long double"
            );
    Matrix();  // Конструктор пустой матрицы
    Matrix(unsigned int col, unsigned int row);  // Конструктор прямоугольной матрицы
    Matrix(unsigned int col);  // Конструктор единичной матрицы
    Matrix(const Matrix& matrix);  // Конструктор копирования матрицы
    Matrix(Matrix&& matrix);  // Конструктор переноса матрицы
    ~Matrix();  // Деструктор


    void print_matrix();
    void set_values();

    Matrix operator+(const Matrix<T>&);
    Matrix operator-(const Matrix<T>&);
    Matrix operator*(const Matrix<T>&);
    Matrix operator*(const T);
    Matrix operator=(Matrix<T>&);
    Matrix operator^(const T) const;
    Matrix operator/(const T) const;
    static Matrix  Exp(const Matrix<T>&, const T);
    Matrix Minor(Matrix<T>&, const unsigned int row, const unsigned int col);
    Matrix transpose();
    double determinant(const Matrix<T>&);


};


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NotSquare("The matrix should be square\n");
Matrix_Exception WrongSize("The matrix should have another size\n");

template <typename T>
Matrix<T>::Matrix() {
    cols = 0;
    rows = 0;
}

template <typename T>
Matrix<T>::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new T[cols*rows];
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new T[rows * cols];
    memcpy(values,matrix.values,rows * cols * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
}

template <typename T>
void Matrix<T>::print_matrix() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
void Matrix<T>::set_values() {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = rand();
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
    if (rows != One.rows) throw WrongSize;
    Matrix res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        res.values[idx] += values[idx];
    }
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& One)  {
    if (rows != One.rows) throw WrongSize;
    Matrix Res(One);
    for (unsigned int idx = 0; idx < One.cols * One.rows; idx++) {
        Res.values[idx] -= values[idx];
    }
    return Res;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& One)  {
    if (rows != One.rows) throw WrongSize;
    Matrix Res(One);
    for (unsigned int row = 0; row < Res.rows; row++) {
        for (unsigned int col = 0; col < Res.cols; col++) {
            Res.values[row* Res.rows + col] = 0.00;
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
Matrix<T> Matrix<T>::operator= (Matrix<T>& one)  {
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
Matrix<T> Matrix<T>::operator= (Matrix<T>&& one)  {
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
    if(cols != rows) throw NotSquare;
    Matrix Res(*this);
    if (coefficient == 0) {
        Matrix one(cols);
        return one;
    }
    if (coefficient == 1) {
        return Res;
    }
    else {
        const Matrix &start(Res);
        for (unsigned int idx = 0; idx < coefficient; idx++){
            Res = Res * start;
        }
        return Res;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator/(const T coefficient) const {
    Matrix Res(cols, rows);
    for(unsigned int idx = 0; idx < rows * cols; ++idx) {
        Res.values[idx] = values[idx]/coefficient;
    }
    return Res;
}

template <typename T>
Matrix<T> Matrix<T>::Exp(const Matrix<T>& A, const unsigned int accuracy = 10){
    if (A.rows != A.cols) throw NotSquare;
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
    int new_row = A.rows -1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix Res = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == col) or (idx / cols == row)) continue;
        Res.values[k++] = A.values[idx];
    }

    return Res;
}
template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix res = {cols, rows};
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
    if(cols != rows) throw NotSquare;
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
protected:
    static unsigned long memory_size;
    static unsigned long total_memory;
public:
    Matrix_Memory<T1>();
    Matrix_Memory<T1>(unsigned int, unsigned int);
    Matrix_Memory<T1>(const Matrix_Memory<T1>&);
    Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
    void output() override;
    ~Matrix_Memory();
};


template <typename T>
Matrix_Memory<T>::Matrix_Memory()
{
    this->rows = 0;
    this->cols = 0;
    this->values = nullptr;
    this->memory_size = 0;
    this->total_memory += this->memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col)
{
    this->rows = row;
    this->cols = col;
    this->values = new T[this->rows * this->cols];
    this->memory_size = row * col * sizeof(T);
    this-> total_memory += this->memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& matrix)
{
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->values = new T[matrix.rows * matrix.cols];
    memcpy(this->values, matrix.values, sizeof(T) * this->rows * this->cols);
    this->memory_size = matrix.memory_size;
    this->total_memory += this->memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& matrix) noexcept
{

this->rows = matrix.rows;
this->cols = matrix.cols;
this->data = matrix.data;
this->memory_size = matrix.memory_size;

matrix.rows = 0;
matrix.cols = 0;
matrix.values = nullptr;
matrix.memory_size = 0;
}


template <typename T>
void Matrix_Memory<T>::output()
{
    std::cout << "Memory allocated for matrix - " << this->total_memory << " byte" << std::endl;
}


int main() {
    Matrix A(5,5);
    A.set_values();
    A.print_matrix();
    Matrix B(5, 5);
    B.set_values();
    B.print_matrix();
    Matrix Sum = A + B;
    Sum.print_matrix();
    Matrix Sub = A - B;
    Sub.print_matrix();
    Matrix Mult = A * B;
    Mult.print_matrix();
    Matrix Mult_double = A * 4;
    Mult_double.print_matrix();
    Matrix Power = A^2;
    Power.print_matrix();
    Matrix Exponent = Matrix::Exp(A);
    return 0;
}
