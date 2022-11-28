#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>

const double eps = pow(10, -5);

class Matrix_error : public std::exception {
public:
    Matrix_error(const char* const &msg) : exception(msg) {}
};

Matrix_error DIVBYZERO ("Divide by zero\n");
Matrix_error NOTSQUARE("Matrix must be square\n");
Matrix_error NOTEQUAL("Matrix must have a same size\n");
Matrix_error MULTERROR("First matrix rows number must be equal to second matrix cols number\n");
Matrix_error MEMORYERROR("Memory are not allocated\n");

class Matrix {
private:
    unsigned int rows;
    unsigned int cols;
    double* values;
public:
    Matrix (unsigned int, unsigned int, double*);
    Matrix (unsigned int, unsigned int);
    Matrix ();
    Matrix (const Matrix&);
    ~Matrix();

    void output();
    unsigned int getrow();
    unsigned int getcol();

    Matrix set_zero();
    Matrix fill_random(unsigned int);
    Matrix fill_array(double*);
    Matrix set_unit();
    Matrix exponent(unsigned int);
    Matrix transpose();
    Matrix minor(const Matrix, const unsigned int, const unsigned int, const unsigned int);
    Matrix invert(const Matrix, unsigned int);
    Matrix determinant(const Matrix, unsigned int);

    Matrix& operator= (Matrix&&) noexcept;
    Matrix& operator= (const Matrix&);
    Matrix& operator+= (const Matrix&);
    Matrix& operator-= (const Matrix&);
    Matrix& operator*= (const Matrix&);
    Matrix& operator*= (const double);
    Matrix& operator/= (const double);

    Matrix& operator+ (const Matrix&);
    Matrix& operator- (const Matrix&);
    Matrix& operator* (const Matrix&);
    Matrix& operator* (const double);
    Matrix& operator/ (const double);

    bool operator!= (const Matrix& matrix);
    bool operator== (const Matrix& matrix);
    friend std::ostream& operator<<(std::ostream& out, Matrix mat);

};

Matrix::Matrix() : rows(0), cols(0), values(NULL){
}

Matrix::Matrix(const Matrix& mat) : rows(mat.rows), cols(mat.cols)
{
    values = new double[rows * cols];
    if (!values) throw MEMORYERROR;
    memcpy(values, mat.values, rows * cols * sizeof(double));
}


Matrix::Matrix(unsigned int num_row, unsigned int num_col, double* value)
{
    rows = num_row;
    cols = num_col;
    for (unsigned int idx = 0; idx < rows*cols; idx++) {
        values[idx] = value[idx];
    }
}

Matrix::Matrix(unsigned int num_row, unsigned int num_col)
{
    rows = num_row;
    cols = num_col;
    values = new double[rows * cols];
    if (!values) throw MEMORYERROR;
}

Matrix::Matrix(Matrix&& matrix) noexcept : values(matrix.values), rows(matrix.rows), cols(matrix.cols)
{
    matrix.values = NULL;
    matrix.rows = 0;
    matrix.cols = 0;
}

Matrix::~Matrix() {
    delete[] this -> values;
}

bool Matrix::operator==(const Matrix &Mat1) {
    if (this -> rows != Mat1.rows || this -> cols != Mat1.cols) return false;
    for (unsigned int number = 0; number < this->rows * this->cols; number++) {
        if (abs(this->values[number] - Mat1.values[number])>eps) return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix &Mat1) {
    return !(*this == Mat1);
}

Matrix Matrix::fill_random(unsigned int n = 10) {
    for(unsigned int number = 0; number < rows*cols; number++) {
        this->values[number] = double(rand()%n);
    }
    return (*this);
}

Matrix Matrix::fill_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
}

Matrix Matrix::set_zero() {  //Задание нулевой матрицы
    for (unsigned int number = 0; number < this->rows * this -> cols; number++) {
        this -> values[number] = 0.0;
    }
    return *this;
}

Matrix Matrix::set_unit() {  //Задание единичной матрицы
    set_zero();  //Сначала вводится нулевая матрица, а потом диагональ заполняется единицами
    for (unsigned int number = 0; number < this->rows * this->cols; number += rows + 1) {
        this -> values[number] = 1.0
    }
}

int main() {
    return 0;

}
