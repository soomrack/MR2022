#include <iostream>
#include <malloc.h>


class Matrix {

public:
    unsigned long int cols;
    unsigned long int rows;
    Matrix (unsigned long int, unsigned int, double*);
    Matrix (unsigned long int, unsigned int);
    Matrix (const Matrix &A);
    ~Matrix();

    /*void matrix_input;
    void matrix_output;*/

    Matrix one_matrix();
    Matrix invert_matrix (const Matrix, unsigned int);
    Matrix determinant (const Matrix, unsigned int);
    Matrix transponent ();
    Matrix matrix_power();
    Matrix matrix_exponent();
    Matrix minor_matrix (Matrix, const unsigned int, const unsigned int, const unsigned int);

    Matrix& operator=(Matrix&&);
    Matrix& operator=(const Matrix);
    Matrix operator+= (const Matrix);
    Matrix operator-= (const Matrix);
    Matrix operator*= (const Matrix);
    Matrix operator*= (const double);
    Matrix operator/= (const double);

    friend std::ostream& operator<<(std::ostream& out, Matrix m);

private:
    double* values;
};

Matrix empty();

Matrix operator+ (const Matrix&);
Matrix operator- (const Matrix&, const Matrix&);
Matrix operator* (const Matrix&,const Matrix&);
Matrix operator* (const Matrix&,const double);
Matrix operator/ (const Matrix&,const double);
Matrix& operator+=(const Matrix&,const Matrix&);
void output(Matrix&);

Matrix::Matrix(const Matrix& matrix) : rows(matrix.rows), cols(matrix.cols) {
    values = new double [cols * rows];
    memcpy(values, matrix.values, cols * rows * sizeof (double));
}

Matrix::Matrix(unsigned int number_col, unsigned int number_rows, double* values) {
    cols = number_col;
    rows = number_rows;
    unsigned int index = rows * cols;
    for (unsigned int number = 0; number < index; number++) {
        values[index] = values[index];
    }
}

Matrix operator+ (const Matrix& mat1, const Matrix& mat2) {
    Matrix summation (mat1);
    summation += mat2;
    return (summation);
}

Matrix operator- (const Matrix& mat1, const Matrix& mat2) {
    Matrix subtruction (mat1);
    subtruction -= mat2;
    return (subtruction);
}

Matrix operator* (const Matrix& matrix, const double n) {
    Matrix multiply (matrix);
    multiply *= n;
    return (multiply);
}

Matrix operator* (const Matrix& mat1, const Matrix& mat2) {
    Matrix temp (mat1);
    temp *= mat2;
    return (temp);
}

Matrix operator/ (const Matrix& matrix, const double n) {
    Matrix division (matrix);
    division /= n;
    return (division);
}

int main() {
    Matrix A(3,3);
    Matrix B(3, 3);

    return 0;
}
