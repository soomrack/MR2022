#include "Matrix.h"
#include <fstream>
#include <exception>
using namespace std;

Matrix_Exception EQUAL("Matrix not equal)\n");
Matrix_Exception NOTSQUARE("Matrix not square!\n");

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    values = nullptr;
}

Matrix::Matrix(unsigned int m_rows, unsigned int m_cols) {
    rows = m_rows;
    cols = m_cols;
    values = new double[cols * rows];
}

Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new double[cols * rows];
    memcpy(values, other.values, rows * cols * sizeof(double)); //функция memcpe() копирует данные other.values в values
}

Matrix::~Matrix() {
    delete[] this->values;
}

Matrix::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols)
{
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

Matrix Matrix::one_number(double n) {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = n;
    return *this;
}

Matrix Matrix::i_number() {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = i;
    return *this;
}

Matrix Matrix::rand_number(int min, int bar) {
    srand(time(nullptr));
    for(int i = 0; i < rows * cols; ++i)
        this->values[i] = double(rand() % bar + min);
    return *this;
}

void Matrix::output() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout  << values[i*cols + j] << " ";
        }
        cout << endl;
    }
}

Matrix& Matrix::operator=(Matrix&& matrix) noexcept
{
    if (this == &matrix) return *this;
    delete[] matrix.values;
    rows = matrix.rows;
    cols = matrix.cols;
    values = matrix.values;
    matrix.values = nullptr;
    return *this;
}

Matrix Matrix::from_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}
//добавить очистку памяти перед
Matrix Matrix::zero(unsigned int m_rows, unsigned int m_cols) {
    delete[] values;
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < m_rows * m_cols; ++i) {
        values[i] = 0.0;
    }
    return *this;
}
//пройти по диагонали
Matrix Matrix::single(unsigned int m_rows, unsigned int m_cols) {
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < rows ; i ++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                values[i * cols + j] = 1.0;
            } else
                values[i * cols + j] = 0.0;
        }
    }
    return *this;
}

bool Matrix::is_equal(const Matrix& other) {
    return ((rows != other.rows) && (cols != other.cols));
}

bool Matrix::is_multiply(const Matrix& other) {
    return (rows == other.cols);
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix Temp(other.rows, other.cols);
    if (is_equal(other)) throw EQUAL;
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] + other.values[i];
    return Temp;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix Temp(this->rows, this->cols);
    if (is_equal(other)) throw EQUAL;
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] - other.values[i];
    return Temp;
}

Matrix Matrix::operator*(double num) {
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num * this->values[i];
    return Temp;
}

Matrix Matrix::operator*(const Matrix& other) {
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

Matrix Matrix::operator/(double num){
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num / this->values[i];
    return Temp;
}

Matrix& Matrix::operator=(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new double[cols * rows];
    for (int i = 0; i < rows*cols; ++i) {
        values[i] = other.values[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, Matrix matrix)
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

double Matrix::get(int i, int j) const {
    return values[i * cols + j];
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    for (int i = 0; i < result.rows; ++i)
        for (int j = 0; j < result.cols; ++j) {
            result.values[i * result.cols + j] = values[j * result.rows + i];
        }
    return result;
}

Matrix Matrix::Minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
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


double Matrix::determinant(const Matrix matrix, unsigned int size)
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
    Matrix A;
    double data[6] = {1, 2, 6,
                      3, 6, 5};
    A = Matrix(1, 1).from_array(data);
    std::cout << A << '\n' << A.determinant(A, 1) << '\t';
    if (A.determinant(A, 1) == 1) cout << "det test passed"; else cout << "det test failed";
}


int main() {
    double det;
    Matrix A, B;
    A = Matrix(3, 3).zero(3, 3);
    B = Matrix(3, 3);
    B = B.single(3, 3);
    std::cout << A;
    std::cout << B;
    try {
        A = A * B;
        std:cout << A;
    }
    catch(const Matrix_Exception& e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    try {
        det = A.determinant(A, 3);
        std::cout << det;
    }
    catch(const Matrix_Exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
}
// virtual void print(); - в родительском классе
// переопределние функции в наследнике virtual void print() overide;
//можно менять функцию в новом классе


