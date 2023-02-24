#include "Matrix.h"
#include <fstream>
#include <exception>
using namespace std;

Matrix_Exception EQUAL("Matrix not equal)\n");
Matrix_Exception NOTSQUARE("Matrix not square!\n");
Matrix_Exception MEMORY_ERROR("Memory error\n");

template <class T>
std::ostream& operator<<(std::ostream& out, Matrix<T> matrix)
{
    {
        for (unsigned int row = 0; row < matrix.rows; row++)
        {
            for (unsigned int col = 0; col < matrix.cols; col++)
            {
                out << matrix.values[row * matrix.cols + col] << "   ";
            }
            out << std::endl;
        }
        out << std::endl;
        return(out);
    }
}

template <class T>
Matrix<T>::Matrix() {
    rows = 0;
    cols = 0;
    values = nullptr;
}

template <typename T>
Matrix<T>::Matrix(unsigned int m_rows, unsigned int m_cols) {
    rows = m_rows;
    cols = m_cols;
    values = new T[cols * rows];
    if (!values) throw MEMORY_ERROR;
}

template <class T>
Matrix<T>::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new T[cols * rows];
    if (!values) throw MEMORY_ERROR;
    memcpy(values, other.values, rows * cols * sizeof(T)); //функция memcpe() копирует данные other.values в values
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] this->values;
}

template <class T>
Matrix<T>::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols)
{
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

template <typename T> //mvkfdmvbklfdgmkblfgb
Matrix<T> Matrix<T>::one_number(T n) {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = n;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::i_number() {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = i;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::rand_number(int min, int bar) {
    srand(time(nullptr));
    for(int i = 0; i < rows * cols; ++i)
        this->values[i] = T(rand() % bar + min);
    return *this;
}


template <typename T>
void Matrix<T>::output() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout  << values[i*cols + j] << " ";
        }
        cout << endl;
    }
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& matrix) noexcept
{
    if (this == &matrix) return *this;
    delete[] matrix.values;
    rows = matrix.rows;
    cols = matrix.cols;
    values = matrix.values;
    matrix.values = nullptr;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::from_array(T* array) {
    memcpy(values, array, rows * cols * sizeof(T));
    return *this;
}
//добавить очистку памяти перед

template <typename T>
Matrix<T> Matrix<T>::zero(unsigned int m_rows, unsigned int m_cols) {
    delete[] values;
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < m_rows * m_cols; ++i) {
        values[i] = 0;
    }
    return *this;
}
//пройти по диагонали
template <typename T>
Matrix<T> Matrix<T>::single(unsigned int m_rows, unsigned int m_cols) {
    cols = m_cols;
    rows = m_rows;
    values = new T[cols * rows];
    for (int i = 0; i < rows ; i ++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                values[i * cols + j] = 1;
            } else
                values[i * cols + j] = 0;
        }
    }
    return *this;
}

template <typename T>
bool Matrix<T>::is_equal(const Matrix& other) {
    return ((rows != other.rows) && (cols != other.cols));
}
template <typename T>
bool Matrix<T>::is_multiply(const Matrix& other) {
    return (rows == other.cols);
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) {
    Matrix Temp(other.rows, other.cols);
    if (is_equal(other)) throw EQUAL;
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] + other.values[i];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) {
    Matrix Temp(this->rows, this->cols);
    if (is_equal(other)) throw EQUAL;
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] - other.values[i];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T num) {
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num * this->values[i];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    if (is_multiply(other) == false) throw EQUAL;
    Matrix result(other.rows, cols);
    result.rows = other.rows;
    result.cols = cols;
    for(int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            double summa = 0.0;
            for (int k = 0; k < other.cols; k++) {
                summa += other.get(i, k) * get(k, j);
            }
            result.values[i * result.cols + j] = summa;
        }
    }
    return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator/(T num){
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num / this->values[i];
    return Temp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    rows = other.rows;
    cols = other.cols;
    values = new T[cols * rows];
    for (int i = 0; i < rows*cols; ++i) {
        values[i] = other.values[i];
    }
    return *this;
}



template <typename T>
T Matrix<T>::get(int i, int j) const {
    return values[i * cols + j];
}

template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < result.rows; ++i)
        for (int j = 0; j < result.cols; ++j) {
            result.values[i * result.cols + j] = values[j * result.rows + i];
        }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::Minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
    Matrix temp(size - 1, size - 1);
    unsigned int shiftrow = 0;
    unsigned int shiftcol;
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        if (rows == row) {
            shiftrow = 1;
        }
        shiftcol = 0;
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) {shiftcol = 1;}
            temp.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow) * size + (cols + shiftcol)];
        }
    }
    return temp;
}

template <typename T>
double Matrix<T>::determinant(const Matrix matrix, unsigned int size)
{
    if (cols != rows) throw NOTSQUARE;
    double det = 0;
    int k = 1;
    if (size == 0)
        return 0;
    if (size == 1)
        return matrix.values[0];
    if (size == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < size; idx++) {
        det += k * matrix.values[idx] * determinant(Minor(matrix, size, 0, idx), size - 1);
        k = -k;
    }
    return det;
}



void test_det() {
    Matrix<double> A;
    double data[6] = {1.0, 2.0, 6.0,
                      3.0, 6.0, 5.0};
    A = Matrix<double>(1, 1).from_array(data);
    if (A.determinant(A, 1) == 1) cout << "det test passed"; else cout << "det test failed";
}

void excepttt() {
    double det;
    Matrix<double> A, B;
    A = Matrix<double>(3, 3).zero(3, 3);
    B = Matrix<double>(3, 3);
    B = B.single(3, 3);
    try {
        A = A * B;
    }
    catch(const Matrix_Exception& e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    try {
        det = A.determinant(A, 3);
    }
    catch(const Matrix_Exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
}
int main() {
    double det;
    Matrix<double> A;
    A = Matrix<double>(3, 3).zero(3, 3);
    A.output();
    det = A.determinant(A, 3);
    cout << det;
}
// virtual void print(); - в родительском классе
// переопределние функции в наследнике virtual void print() overide;
//можно менять функцию в новом классе


