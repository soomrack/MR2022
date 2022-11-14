//
// Created by user on 24.10.2022.
//

#include "Matrix.h"


Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(unsigned int r_num, unsigned int c_num) : rows(r_num), cols(c_num) {
    values = new double[rows * cols];
}


Matrix::Matrix(const Matrix &mat) : rows(mat.rows), cols(mat.cols), swap_num(mat.swap_num) {
    values = new double[rows * cols];
    memcpy(values, mat.values, sizeof(double) * rows * cols);
}


Matrix::Matrix(Matrix &&mat) noexcept: values(mat.values), rows(mat.rows), cols(mat.cols), swap_num(mat.swap_num) {
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}


Matrix& Matrix::operator=(const Matrix &mat) {
    if (this != &mat) {
        delete[] values;
        rows = mat.rows;
        cols = mat.cols;
        memcpy(values, mat.values, rows * cols * sizeof(double));
    }
    return *this;
}


Matrix& Matrix::operator=(Matrix &&mat) noexcept {  // Оператор перемещающего присваивания
    if (this != &mat) {
        delete[] values;
        rows = mat.rows;
        cols = mat.cols;
        values = mat.values;
        mat.values = nullptr;
    }
    return *this;
}


Matrix Matrix::fill_value(double value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) values[idx] = value;
    return *this;
}


double Matrix::get(unsigned int row, unsigned int col) {
    // TODO: Проверка if (row > rows || col > cols) return NAN;
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


bool Matrix::operator==(const Matrix &mat) {
    Matrix mat1 = *this;
    if (mat1.cols != mat.cols || mat1.rows != mat.rows) return false;
    for (unsigned int idx = 0; idx < mat1.cols * mat1.rows; idx++) {
        if (abs(mat1.values[idx] - mat.values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::fill_random(int min_value, int max_value) {
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        values[idx] = min_value + (double) rand() / (double) RAND_MAX * (max_value - min_value);
    }
    return *this;
}


Matrix Matrix::fill_identity() {
    // TODO: Проверка if (rows != cols)
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        this->values[idx] = idx % (rows + 1) == 0 ? 1.0 : 0.0;
    }
    return *this;
}


Matrix Matrix::fill_from_array(double *array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}


bool Matrix::is_identity() {
    if (cols != rows) return false;
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        if (idx % (rows + 1) == 0) {
            if (abs(values[idx] - 1) > EPS) return false;
        } else {
            if (abs(values[idx]) > EPS) return false;
        }
    }
    return true;
}


Matrix Matrix::operator+(const Matrix &mat2) const {
    // TODO: Проверка if (this->rows != mat2.rows || this->cols != mat2.cols)
    const Matrix &mat1 = *this;
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = mat1.values[idx] + mat2.values[idx];
    }
    return res;
}


Matrix Matrix::operator-(const Matrix &mat2) const {
    // TODO: Проверка if (this->rows != mat2.rows || this->cols != mat2.cols)
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

Matrix Matrix::operator*(const Matrix &mat2) const {
    // TODO: Проверка if (this->cols != mat2.rows) в класс исключений
    Matrix mat1 = *this;
    Matrix res = {mat1.rows, mat1.cols};
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            double summa = 0.0;
            for (unsigned int idx = 0; idx < mat1.cols; idx++) {
                summa += mat1.values[row * mat1.cols + idx] * mat2.values[idx * mat2.cols + col];
            }
            res.values[res.cols * row + col] = summa;
        }
    }
    return res;
}


Matrix Matrix::transpose() {
    // TODO: Проверка на квадратную форму в класс исключений
    Matrix res = {this->cols, this->rows};
    int counter = 0;
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = this->values[col * res.cols + row];
        }
    }
    return res;
}


void Matrix::swap_rows(unsigned int row1, unsigned int row2){
    auto temp = new double[cols];
    memcpy(temp, this->operator[](row1), cols * sizeof(double));
    memcpy(this->operator[](row1), this->operator[](row2), cols * sizeof(double));
    memcpy(this->operator[](row2), temp, cols * sizeof(double));
    this->swap_num++;
}


Matrix Matrix::upper_triangle() {
    // TODO: Проверка на квадратную форму в класс исключений
    Matrix mat = *this;
    for (unsigned int step = 0; step < mat.cols; step++) {
        unsigned int non_zero_row = step;
        // Переход к следующему столбцу, все элементы столбца нулевые
        while (mat.values[non_zero_row * mat.cols + step] == 0 && non_zero_row != mat.rows - 1) non_zero_row++;
        if (non_zero_row != step) mat.swap_rows(non_zero_row, step);
    }
    for (unsigned int col = 0; col < mat.cols - 1; col++) {
        if (mat.values[col + mat.cols * col] != 0) {
            for (unsigned int row = col + 1; row < mat.rows; row++) {
                double factor = mat.values[col + mat.cols * row] / mat.values[col + mat.cols * col];
                for (unsigned int idx = col; idx < mat.cols; idx++) {
                    mat.values[idx + mat.cols * row] -= mat.values[idx + mat.cols * col] * factor;
                }
            }
        }
    }
    return mat;
}


double Matrix::det() {
    // TODO: Проверка на квадратную форму в класс исключений
    Matrix temp = this->upper_triangle();
    double res = 1;
    for (unsigned int idx = 0; idx < temp.rows * temp.cols; idx += temp.cols + 1) {
        res *= temp.values[idx];
    }
    return res * pow(-1, temp.swap_num);
}


double Matrix::trace() {
    // TODO: Проверка на квадратную форму в класс исключений
    double res = 0.0;
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx += this->cols + 1) res += this->values[idx];
    return res;
}


// Минор матрицы по строке minor_row и столбцу minor_col
Matrix Matrix::minor(const unsigned int minor_row, const unsigned int minor_col){
    Matrix mat = *this;
    Matrix temp = Matrix(mat.rows - 1, mat.cols - 1);
    int minor_index = 0;
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++) {
            if (row != minor_row && col != minor_col) {
                temp.values[minor_index++] = mat.values[row * mat.rows + col];
            }
        }
    }
    return temp;
}


Matrix Matrix::inv() {
    // TODO: Проверка if (mat.cols != mat.rows){
    Matrix mat = *this;
    Matrix ans = {mat.rows, mat.cols};
    double determinant = mat.det();
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
                    mat.minor(row, col).det() / determinant;
            // неправильные знаки в обратной матрице если используется перестановка строк
        }
    }
    return ans;
}