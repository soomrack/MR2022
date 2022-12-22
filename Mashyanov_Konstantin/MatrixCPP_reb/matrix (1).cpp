
#include "matrix.h"
#include <cmath>

Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}


Matrix::Matrix(unsigned int r_num, unsigned int c_num) {
    rows = r_num;
    cols = c_num;
    values = new double[rows * cols];
    if (!values) throw MatrixException("Error: unable to allocate memory");
}


Matrix::Matrix(const Matrix& mat) {
    rows = mat.rows;
    cols = mat.cols;
    values = new double[rows * cols];
    if (!values) throw MatrixException("Error: unable to allocate memory");
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

    if (row > rows || col > cols) throw
                MatrixException("Index error: one of the indexes is bigger than matrix size");
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
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
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
        if (idx % (rows) != 0 && fabs(values[idx]) > EPS) return false;
    }
    return true;
}


Matrix Matrix::operator+(const Matrix& mat) const {
    if (this->rows != mat.rows || this->cols != mat.cols) throw
                MatrixException("Matrices must be the same size");
    Matrix res = {rows, cols};
    for (unsigned int idx = 0; idx < rows * cols; idx++) {
        res.values[idx] = this->values[idx] + mat.values[idx];
    }
    return res;
}


Matrix Matrix::operator-(const Matrix& mat2) const {
    if (this->rows != mat2.rows || this->cols != mat2.cols) throw
                MatrixException("Matrices must be the same size");
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
    if (this->cols != mat2.rows) throw
                MatrixException("Error: First matrix cals must be equal to second matrix rows");
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


Matrix Matrix::transpose() {
    // TODO: Проверка на квадратную форму в класс исключений
    Matrix res (cols, rows);
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.values[row * res.cols + col] = this->values[col * res.rows + row];
        }
    }
    return res;
}


void Matrix::swap_rows(unsigned int row1, unsigned int row2){
    auto temp = new double[cols];
    memcpy(temp, this->operator[](row1), cols * sizeof(double));
    memcpy(this->operator[](row1), this->operator[](row2), cols * sizeof(double));
    memcpy(this->operator[](row2), temp, cols * sizeof(double));
}


unsigned int Matrix::upper_triangle() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    unsigned int swap_num = 0;
    for (unsigned int step = 0; step < this->cols; step++) {
        unsigned int non_zero_row = step;
        // Переход к следующему столбцу, все элементы столбца нулевые
        while (this->values[non_zero_row * this->cols + step] == 0 && non_zero_row != this->rows - 1) non_zero_row++;
        if (non_zero_row == step) continue;
        this->swap_rows(non_zero_row, step);
        swap_num += 1;
    }
    for (unsigned int col = 0; col < this->cols - 1; col++) {
        if (this->values[col + this->cols * col] == 0) continue;
        for (unsigned int row = col + 1; row < this->rows; row++) {
            double factor = this->values[col + this->cols * row] / this->values[col + this->cols * col];
            for (unsigned int idx = col; idx < this->cols; idx++) {
                this->values[idx + this->cols * row] -= this->values[idx + this->cols * col] * factor;
            }
        }
    }
    return swap_num;
}


double Matrix::det() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix temp = *this;
    unsigned int swap_num = temp.upper_triangle();
    double res = 1;
    for (unsigned int idx = 0; idx < temp.rows * temp.cols; idx += temp.cols + 1) {
        res *= temp.values[idx];
    }
    return res * (1 - 2 * (swap_num % 2 == 1));
}


double Matrix::trace() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
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
            if (row == minor_row || col == minor_col) continue;
            temp.values[minor_index++] = mat.values[row * mat.rows + col];
        }
    }
    return temp;
}


Matrix Matrix::inv() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix mat = *this;
    Matrix ans = {mat.rows, mat.cols};
    double determinant = mat.det();
    for (unsigned int row = 0; row < mat.rows; row++){
        for (unsigned int col = 0; col < mat.cols; col++){
            ans.values[col * ans.rows + row] = pow(-1, row + col) *
                                               mat.minor(row, col).det() / determinant;
        }
    }
    return ans;
}


Matrix Matrix::exp() {
    if (rows != cols) throw MatrixException("Error: Matrix must be square");
    Matrix ans = *this;
    if (this->is_diagonal()) {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            if (idx % (rows + 1) == 0 ) ans.values[idx] = ::exp(ans.values[idx]);
            else ans.values[idx] = 0;
        }
        return ans;
    }
    // Если матрица не диагональная, то вычисляем через степенной ряд
    int max_iter = 20;
    Matrix pow = Matrix(this->rows, this->cols).set_identity();
    ans.set_identity();
    unsigned long long int factorial = 1;
    for(int iter = 1; iter < max_iter; iter++) {
        pow *= *this;
        factorial *= iter;
        ans += pow / factorial;
    }
    return ans;
}

