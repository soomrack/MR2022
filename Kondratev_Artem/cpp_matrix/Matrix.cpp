#include "Matrix.h"


MatrixException WRONG_PARAMETERS(1, "matrix parameters are less than zero");
MatrixException NULL_MEMORY(2, "memory is not allocated");
MatrixException ADDITION_ERROR(3, "wrong matrix sizes for addition");
MatrixException SUBTRACTION_ERROR(4, "wrong matrix sizes for subtraction");
MatrixException NAN_NUMBER(5, "number is NAN");
MatrixException MULTIPLICATION_ERROR(6, "wrong matrix sizes for multiplication");
MatrixException DIVISION_BY_ZERO(7, "division_by_zero");
MatrixException NOT_SQUARE(8, "matrix is not square");
MatrixException WRONG_LENGTH(9, "length of vector is wrong");
MatrixException ZERO_LENGTH(10, "rows || cols is/are zero");


template<class T>
Matrix<T>::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    data = nullptr;
    values = nullptr;
}


template<typename T>
Matrix<T>::Matrix(int input_rows, int input_cols) {
    if (input_rows <= 0 || input_cols <= 0) {
        throw WRONG_PARAMETERS;
    }
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    data = new T *[rows];
    values = new T[size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
}


template<typename T>
Matrix<T>::Matrix(int input_rows, int input_cols, T number): Matrix{input_rows, input_cols} {
    for (int cell = 0; cell < size; cell++)
        values[cell] = number;
}


template<typename T>
Matrix<T>::Matrix(int input_rows, int input_cols, const std::vector<T> &vector): Matrix<T>(input_rows, input_cols) {
    if (size != vector.size()) {
        throw WRONG_LENGTH;
    }
    for (int cell = 0; cell < size; cell++)
        values[cell] = vector[cell];
}


template<typename T>
Matrix<T>::Matrix(int identity_size): Matrix<T>(identity_size, identity_size) {
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            data[row][col] = (row == col) ? 1 : 0;
}


template<typename T>
Matrix<T>::Matrix(const Matrix<T> &other) {
    rows = other.rows;
    cols = other.cols;
    size = other.size;
    data = new T *[rows];
    values = new T[size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    std::memcpy(values, other.values, sizeof(T) * other.size);
}


template<typename T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept {
    rows = other.rows;
    cols = other.cols;
    size = other.size;
    data = other.data;
    values = other.values;
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw NULL_MEMORY;
    }
    other.data = nullptr;
    other.values = nullptr;
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
}


template<typename T>
Matrix<T>::~Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    delete[] data;
    delete[] values;
}


template<typename T>
int Matrix<T>::get_rows() const {
    return rows;
}


template<typename T>
int Matrix<T>::get_cols() const {
    return cols;
}


template<typename T>
int Matrix<T>::get_size() const {
    return size;
}


template<typename T>
T Matrix<T>::get_value(int cell) const {
    if (cell < 0) {
        throw WRONG_PARAMETERS;
    }
    return values[cell];
}


template<typename T>
T Matrix<T>::get_value(int row, int col) const {
    if (row < 0 || col < 0) {
        throw WRONG_PARAMETERS;
    }
    return data[row][col];
}


template<typename T>
void Matrix<T>::set_value(int cell, T number) {
    if (cell < 0) {
        throw WRONG_PARAMETERS;
    }
    values[cell] = number;
}


template<typename T>
void Matrix<T>::set_value(int row, int col, T number) {
    if (row < 0 || col < 0) {
        throw WRONG_PARAMETERS;
    }
    data[row][col] = number;
}


template<typename T>
void Matrix<T>::output() const {
    if (data == nullptr || values == nullptr) {
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << std::scientific << std::setw(13) << data[row][col] << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> const &other) {
    if (this != &other) {
        delete[] data;
        delete[] values;
        rows = other.rows;
        cols = other.cols;
        size = rows * cols;
        data = new T *[rows];
        values = new T[size];
        if (data == nullptr || values == nullptr) {
            delete[] data;
            delete[] values;
            throw NULL_MEMORY;
        }
        for (int row = 0; row < rows; row++)
            data[row] = values + row * cols;
        std::memcpy(values, other.values, sizeof(T) * other.size);
    }
    return *this;
}


template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T> &&other) noexcept {
    if (this != &other) {
        delete[] data;
        delete[] values;
        rows = other.rows;
        cols = other.cols;
        size = rows * cols;
        data = other.data;
        values = other.values;
        other.data = nullptr;
        other.values = nullptr;
        for (int row = 0; row < rows; row++)
            data[row] = values + row * cols;
    }
    return *this;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw ADDITION_ERROR;
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += matrix.values[cell];
    return sum_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(T number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += number;
    return sum_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw SUBTRACTION_ERROR;
    }
    Matrix<T> sub_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sub_matrix.values[cell] -= matrix.values[cell];
    return sub_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const &matrix) const {
    if (cols != matrix.rows) {
        throw MULTIPLICATION_ERROR;
    }
    Matrix<T> multiplied_matrix(cols, matrix.rows);
    for (int row = 0; row < multiplied_matrix.rows; row++)
        for (int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.data[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.data[row][col] += data[row][k] * matrix.data[k][col];
        }
    return multiplied_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(T number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    Matrix<T> multiplied_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        multiplied_matrix.values[cell] *= number;
    return multiplied_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::minor_init(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw WRONG_PARAMETERS;
    }
    Matrix<T> minor(rows - 1, cols - 1);
    int row_shift = 0;
    for (int row = 0; row < minor.rows; row++) {
        if (excluded_row == row)
            row_shift++;
        int col_shift = 0;
        for (int col = 0; col < minor.cols; col++) {
            if (col == excluded_col) {
                col_shift++;
            }
            minor.data[row][col] = data[row + row_shift][col + col_shift];
        }
    }
    return minor;
}


template<typename T>
T Matrix<T>::determinant() const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (rows == 0 || cols == 0) {
        throw ZERO_LENGTH;
    }
    T determinant = 0;
    if (rows == 1) {
        determinant = data[0][0];
        return determinant;
    }
    T k = 1.0;
    for (int col = 0; col < cols; col++) {
        Matrix<T> minor = minor_init(0, col);
        determinant += k * data[0][col] * minor.determinant();
        k = -k;
    }
    return determinant;
}


template<typename T>
Matrix<T> Matrix<T>::transposition() const {
    int new_rows = cols;
    int new_cols = rows;
    Matrix<T> transposed_matrix(new_rows, new_cols);
    for (int row = 0; row < transposed_matrix.rows; row++)
        for (int col = 0; col < transposed_matrix.cols; col++)
            transposed_matrix.data[row][col] = data[col][row];
    return transposed_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::minor_transformation(const Matrix<T> &matrix) {
    if (matrix.rows != matrix.cols) {
        throw NOT_SQUARE;
    }
    Matrix<T> transformed_matrix(matrix.rows, matrix.cols);
    if (matrix.rows == 1) {
        transformed_matrix = matrix;
        return transformed_matrix;
    }
    for (int row = 0; row < matrix.rows; row++) {
        for (int col = 0; col < matrix.cols; col++) {
            Matrix<T> minor = matrix.minor_init(row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            transformed_matrix.data[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::inversion() const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix<T> transformed_matrix = minor_transformation(this->transposition());
    Matrix<T> inverse_matrix = transformed_matrix * (1 / this->determinant());
    return inverse_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> &matrix) const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix<T> inverse_matrix = matrix.inversion();
    Matrix<T> inverse_multiplied_matrix(cols, inverse_matrix.rows);
    for (int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for (int col = 0; col < inverse_multiplied_matrix.cols; col++) {
            inverse_multiplied_matrix.data[row][col] = 0;
            for (int k = 0; k < cols; k++)
                inverse_multiplied_matrix.data[row][col] += data[row][k] * inverse_matrix.data[k][col];
        }
    return inverse_multiplied_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator/(T number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    if (std::abs(number) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix<T> divided_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        divided_matrix.values[cell] /= number;
    return divided_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::power(int power) const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (power == 0) {
        return Matrix<T>(this->rows);
    }
    if (power == 1) {
        return *this;
    }
    Matrix<T> powered_matrix;
    if (power > 1) {
        powered_matrix = *this;
    }
    if (power < 0) {
        powered_matrix = this->inversion();
        power = -power;
    }
    for (int k = 1; k < power; k++) {
        powered_matrix = powered_matrix * *this;
    }
    return powered_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::exp(const Matrix<T> &matrix, int STEPS) {
    if (matrix.rows != matrix.cols) {
        throw NOT_SQUARE;
    }
    Matrix<T> exp_matrix(matrix.rows);
    T k = 1.0;
    for (int s = 1; s < STEPS; s++) {
        k *= s;
        exp_matrix = exp_matrix + matrix.power(s) / k;
    }
    return exp_matrix;
}


template<typename T>
int Matrix<T>::is_equal(Matrix<T> matrix1, Matrix<T> matrix2) {
    if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols) {
        return 1;
    }
    for (int cell = 0; cell < matrix1.size; cell++)
        if (std::abs(matrix1.values[cell] - matrix2.values[cell]) >= Matrix::EPSILON) {
            return 1;
        }
    return 0;
}


template
class Matrix<double>;

template
class Matrix<float>;
