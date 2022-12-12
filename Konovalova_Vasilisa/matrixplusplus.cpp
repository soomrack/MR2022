#include <iostream>
#include <cstdlib>
#include <cstring>

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NOTSQUARE("Make matrix square\n");
Matrix_Exception SIZEERROR("Change a size\n");
Matrix_Exception DIVISIONERROR ("Can't divide by zero\n");


class Matrix {
private:
    unsigned int cols;
    unsigned int rows;
    double* values;

public:
    Matrix();
    Matrix(unsigned int col, unsigned int row);
    Matrix(unsigned int col);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();


    void print_matrix();
    void set_values(int max_value);

    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator*(double number) const;
    Matrix operator=(Matrix& matrix);
    Matrix operator=(Matrix&& matrix);
    Matrix operator^(const int number) const;
    Matrix operator/(const double number) const;
    static Matrix  exp(const Matrix& A, const unsigned int accuracy);
    Matrix minor(Matrix& mat1, unsigned int row, unsigned int col);
    Matrix transpose();
    double determinant(Matrix matrix);


};



Matrix::Matrix() {
    cols = 0;
    rows = 0;
    values = nullptr;
}


Matrix::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    values = new double[cols*rows];
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        values[idx] = 0.0;
    }
}


Matrix::Matrix(const Matrix& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = new double[rows * cols];
    memcpy(values,matrix.values,rows * cols * sizeof(double));
}


Matrix::Matrix(Matrix&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    values = matrix.values;
    matrix.values = nullptr;
}


void Matrix::print_matrix() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << values[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::set_values(int max_value = 10) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        values[index] = rand() % max_value;
    }
}


Matrix::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    values = new double[cols * rows];
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            values[row * cols + col] = (row == col) ? 1.0 : 0.0;

        }
    }
}


Matrix Matrix::operator+ (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] += values[idx];
    }
    return result;
}


Matrix Matrix::operator- (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.values[idx] -= values[idx];
    }
    return result;
}


Matrix Matrix::operator* (const Matrix& matrix) const {
    if (rows != matrix.rows) throw SIZEERROR;
    Matrix result(matrix);
    for (unsigned int row = 0; row <result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row* result.rows + col] = 0.00;
            for (unsigned int k = 0; k < result.cols; k++) {
                result.values[row * result.cols + col] += values[row * cols + k] * matrix.values[k * result.cols + col];
            }
        }
    }
    return result;
}


Matrix Matrix::operator* (const double coefficient) const {
    Matrix result(cols, rows);
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        result.values[idx] = values[idx] * coefficient;
    }
    return result;
}



Matrix Matrix::operator= (Matrix& matrix)  {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]values;
    values = new double [cols * rows];
    memcpy(values, matrix.values, rows * cols * sizeof(double));
    return *this;
}


Matrix Matrix::operator= (Matrix&& matrix)  {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]values;
    values = matrix.values;
    matrix.values = nullptr;
    return *this;
}


Matrix Matrix::operator^(int number) const {
    if(cols != rows) throw NOTSQUARE;
    Matrix result(*this);
    if (number == 0) {
        Matrix matrix(cols);
        return matrix;
    }
    if (number == 1) {
        return result;
    }
    const Matrix &start(result);
    for (unsigned int idx = 0; idx < number; idx++){
        result = result * start;
    }
    return result;
}


Matrix Matrix::operator/(const double number) const {
    if (number == 0) throw DIVISIONERROR;
    Matrix result(cols, rows);
    for(unsigned int idx = 0; idx < rows * cols; ++idx) {
        result.values[idx] = values[idx]/number;
    }
    return result;
}


Matrix Matrix::exp(const Matrix& A, const unsigned int accuracy = 10){
    if (A.rows != A.cols) throw NOTSQUARE;
    Matrix one(A.cols);
    Matrix result = one + A;
    double factorial = 1;
    for (int step = 1; step < accuracy; step++) {
        factorial *= step;
        result = result + (A ^ step) / factorial;
    }
    return result;
}


Matrix Matrix::minor(Matrix& A, unsigned int row, unsigned int col) {
    int new_row = A.rows -1;
    int new_col = A.cols - 1;
    if (row >= A.rows) new_row++;
    if (col >= A.cols) new_col++;

    Matrix result = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == col) or (idx / cols == row)) continue;
        result.values[k++] = A.values[idx];
    }

    return result;
}

Matrix Matrix::transpose() {
    Matrix result = {cols, rows};
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row * result.cols + col] = values[col * result.cols + row];
        }
    }
    return result;
}




int main() {
    Matrix mat1(3,3);
    mat1.set_values();
    mat1.print_matrix();
    Matrix mat2(3, 3);
    mat2.set_values();
    mat2.print_matrix();
    Matrix sum = mat1 + mat2;
    sum.print_matrix();
    Matrix sub = mat1 - mat2;
    sub.print_matrix();
    Matrix mult = mat1 * mat2;
    mult.print_matrix();
    Matrix mult_number = mat1* 2;
    mult_number.print_matrix();
    Matrix pow = mat1^2;
    pow.print_matrix();
    Matrix exp = Matrix::exp(mat1);
    exp.print_matrix();
    return 0;
}