#include "Matrix.h"


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
        throw MatrixException("matrix parameters are less than zero");
    }
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    data = new T *[rows];
    values = new T[size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("memory is not allocated");
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
        throw MatrixException("length of vector is wrong");
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
Matrix<T>::Matrix(const Matrix<T>& other) {
    rows = other.rows;
    cols = other.cols;
    size = other.size;
    data = new T* [rows];
    values = new T[size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("memory is not allocated");
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    std::memcpy(values, other.values, sizeof(T) * other.size);
}


template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
    rows = other.rows;
    cols = other.cols;
    size = other.size;
    data = other.data;
    values = other.values;
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
int Matrix<T>::getRows() const {
    return rows;
}


template<typename T>
int Matrix<T>::getCols() const {
    return cols;
}


template<typename T>
int Matrix<T>::getSize() const {
    return size;
}


template<typename T>
T Matrix<T>::getValue(int cell) const {
    if (cell < 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    return values[cell];
}


template<typename T>
T Matrix<T>::getValue(int row, int col) const {
    if (row < 0 || col < 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    return data[row][col];
}


template<typename T>
void Matrix<T>::setValue(int cell, T number) {
    if (cell < 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    values[cell] = number;
}


template<typename T>
void Matrix<T>::setValue(int row, int col, T number) {
    if (row < 0 || col < 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    data[row][col] = number;
}


template<typename T>
void Matrix<T>::output() const {
    if (data == nullptr || values == nullptr) {
        throw MatrixException("memory is not allocated");
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
            throw MatrixException("memory is not allocated");
        }
        for (int row = 0; row < rows; row++)
            data[row] = values + row * cols;
        std::memcpy(values, other.values, sizeof(T) * other.size);
    }
    return *this;
}


template<typename T>
Matrix<T> &Matrix<T>::operator=(Matrix<T>&& other) noexcept {
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
        throw MatrixException("wrong matrix sizes for addition");
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += matrix.values[cell];
    return sum_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator+(T number) const {
    if (std::isnan(number)) {
        throw MatrixException("number is NAN");
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += number;
    return sum_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator-(Matrix<T> const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw MatrixException("wrong matrix sizes for subtraction");
    }
    Matrix<T> sub_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sub_matrix.values[cell] -= matrix.values[cell];
    return sub_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const &matrix) const {
    if (cols != matrix.rows) {
        throw MatrixException("wrong matrix sizes for multiplication");
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
        throw MatrixException("number is NAN");
    }
    Matrix<T> multiplied_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        multiplied_matrix.values[cell] *= number;
    return multiplied_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::minorInit(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw MatrixException("matrix parameters are less than zero");
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
        throw MatrixException("matrix is not square");
    }
    if (rows == 0 || cols == 0) {
        throw MatrixException("rows || cols is/are zero");
    }
    T determinant = 0;
    if (rows == 1) {
        determinant = data[0][0];
        return determinant;
    }
    T k = 1.0;
    for (int col = 0; col < cols; col++) {
        Matrix<T> minor = minorInit(0, col);
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
Matrix<T> Matrix<T>::minorTransformation(const Matrix<T> &matrix) {
    if (matrix.rows != matrix.cols) {
        throw MatrixException("matrix is not square");
    }
    Matrix<T> transformed_matrix(matrix.rows, matrix.cols);
    if (matrix.rows == 1) {
        transformed_matrix = matrix;
        return transformed_matrix;
    }
    for (int row = 0; row < matrix.rows; row++) {
        for (int col = 0; col < matrix.cols; col++) {
            Matrix<T> minor = matrix.minorInit(row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            transformed_matrix.data[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::inversion() const {
    if (rows != cols) {
        throw MatrixException("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException("division_by_zero");
    }
    Matrix<T> transformed_matrix = minorTransformation(this->transposition());
    Matrix<T> inverse_matrix = transformed_matrix * (1 / this->determinant());
    return inverse_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::operator/(const Matrix<T> &matrix) const {
    if (rows != cols) {
        throw MatrixException("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException("division_by_zero");
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
        throw MatrixException("number is NAN");
    }
    if (std::abs(number) < EPSILON) {
        throw MatrixException("division_by_zero");
    }
    Matrix<T> divided_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        divided_matrix.values[cell] /= number;
    return divided_matrix;
}


template<typename T>
Matrix<T> Matrix<T>::power(int power) const {
    if (rows != cols) {
        throw MatrixException("matrix is not square");
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
        throw MatrixException("matrix is not square");
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
int Matrix<T>::isEqual(Matrix<T> matrix1, Matrix<T> matrix2) {
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
