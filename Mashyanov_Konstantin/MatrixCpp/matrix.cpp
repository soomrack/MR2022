
#include "matrix.h"
#include <cmath>

Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(unsigned int r_num, unsigned int c_num) {
    rows = r_num;
    cols = c_num;
    values = new double[rows * cols];
    if (!values) {
        std::cerr << "Error: unable to allocate memory\n";
        exit(1);
    }
}


Matrix::Matrix(const Matrix& mat) {
    rows = mat.rows;
    cols = mat.cols;
    values = new double[rows * cols];
    if (!values) {
        std::cerr << "Error: unable to allocate memory\n";
        exit(1);
    }
    memcpy(values, mat.values, sizeof(double) * rows * cols);
}


Matrix::Matrix(Matrix&& mat) noexcept {
    values = mat.values;
    rows = mat.rows;
    cols = mat.cols;
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}


Matrix& Matrix::operator=(const Matrix& mat) {
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    memcpy(values, mat.values, rows * cols * sizeof(double));
    return *this;
}


Matrix& Matrix::operator=(Matrix&& mat) noexcept {  // Оператор перемещающего присваивания
    if (this == &mat) return *this;
    delete[] values;
    rows = mat.rows;
    cols = mat.cols;
    values = mat.values;
    mat.values = nullptr;
    return *this;
}


double Matrix::get(unsigned int row, unsigned int col) {

    if (row > rows || col > cols) {
        std::cerr << ("Index error: one of the indexes is bigger than matrix size");
        exit(1);
    }
    return values[col + row * cols];
}


void Matrix::set(unsigned int row, unsigned int col, double value) {
    if (row > rows || col > cols) return;
    values[col + row * cols] = value;
}


double* Matrix::operator[](unsigned int idx) {
    if (idx > rows) return nullptr;
    return values + idx * cols;
}


bool Matrix::operator==(const Matrix& mat) {
    if (this->cols != mat.cols || this->rows != mat.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
        if (fabs(this->values[idx] - mat.values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::set_value(double value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) values[idx] = value;
    return *this;
}


Matrix Matrix::set_random(int min_value, int max_value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value);
    }
    return *this;
}


Matrix Matrix::set_identity() {
    if (rows != cols) {
        std::cerr << "Error: Matrix must be square\n";
        exit(1);
    }
    this->set_value(0.0);
    for (unsigned int idx = 0; idx < rows * cols; idx += cols + 1) {
        this->values[idx] = 1.0;
    }
    return *this;
}


Matrix Matrix::fill_from_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}


bool Matrix::is_identity() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) == 0) {
            if (fabs(values[idx] - 1) > EPS) return false;
        } else {
            if (fabs(values[idx]) > EPS) return false;
        }
    }
    return true;
}


bool Matrix::is_diagonal() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) != 0 && fabs(values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::operator+(const Matrix& mat) const {
    if (this->rows != mat.rows || this->cols != mat.cols) {
        std::cerr <<"Matrices must be the same size\n";
        exit(1);
    }
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] + mat.values[idx];
    }
    return res;
}


Matrix Matrix::operator-(const Matrix& mat2) const {
    if (this->rows != mat2.rows || this->cols != mat2.cols) {
        std::cerr << "Matrices must be the same size\n";
        exit(1);
    }
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] - mat2.values[idx];
    }
    return res;
}


Matrix Matrix::operator*(const double scalar) const {
    Matrix res = *this;
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] *= scalar;
    return res;
}


Matrix Matrix::operator/(const double scalar) const {
    Matrix res = *this;
    for (unsigned int idx = 0; idx < rows * cols; idx++) res.values[idx] /= scalar;
    return res;
}

Matrix Matrix::operator*(const Matrix& mat2) const {
    if (this->cols != mat2.rows) {
        std::cerr << "Error: First matrix cals must be equal to second matrix rows\n";
        exit(1);
    }
    Matrix res = {this->rows, this->cols};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            double summa = 0.0;
            for (unsigned int idx = 0; idx < this->cols; idx++) {
                summa += this->values[row * this->cols + idx] * mat2.values[idx * mat2.cols + col];
            }
            res.values[res.cols * row + col] = summa;
        }
    }
    return res;
}


void Matrix::print(){
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            std::cout << values[col + row * cols] << " ";
        }
        if (row != rows - 1) std::cout << "\n";
    }
}