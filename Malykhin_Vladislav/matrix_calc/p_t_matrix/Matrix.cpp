#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix() noexcept {
    rows = 0;
    cols = 0;
    data = nullptr;
    values = nullptr;
}


template <typename T>
Matrix<T>::Matrix(int input_rows, int input_cols) {
    if(input_rows <= 0 || input_cols <= 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    rows = input_rows;
    cols = input_cols;
    data = new T *[rows];
    values = new T[rows * cols];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("memory is not allocated");
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
}


template <typename T>
Matrix<T>::Matrix(int input_rows, int input_cols,T number): Matrix{input_rows, input_cols}  {
    for (int cell = 0; cell < rows * cols; cell++)
        values[cell] = number;
}


template<typename T>
Matrix<T>::Matrix(int input_rows, int input_cols, const std::vector<T> &vector) : Matrix(input_rows, input_cols){
    if (rows * cols != vector.size()) {
        throw MatrixException("length of vector is wrong");
    }
    for (int cell = 0; cell < rows * cols; cell++)
        values[cell] = vector[cell];
}


template<typename T>
Matrix<T>::Matrix(int identity_size): Matrix<T>(identity_size, identity_size) {
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            data[row][col] = (row == col) ? 1 : 0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    rows = other.rows;
    cols = other.cols;
    data = new T* [rows];
    values = new T[rows * cols];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("memory is not allocated");
    }
    std::memcpy(values, other.values, sizeof(T) * other.rows * other.cols);
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
}


template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
    rows = other.rows;
    cols = other.cols;
    data = other.data;
    values = other.values;
    other.data = nullptr;
    other.values = nullptr;
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
}


template<typename T>
Matrix<T>::~Matrix() noexcept{
    rows = 0;
    cols = 0;
    delete[] data;
    delete[] values;
}




template <typename T>
int Matrix<T>::get_rows() const {
    return rows;
}


template <typename T>
int Matrix<T>::get_cols() const {
    return cols;
}


template <typename T>
int Matrix<T>::get_size() const {
    return cols * rows;
}


template <typename T>
T Matrix<T>::get_cell(int row, int column) const {
    if (row < 0 || column < 0) {
        throw MatrixException ("matrix parameters are less than zero");
    }
    return data[row][column];
}


template <typename T>
void Matrix<T>::print() const {
    if (data == nullptr || values == nullptr) {
        throw MatrixException("memory is not allocated");
    }
    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < cols; column++)
            std::cout << std::scientific << std::setw(13) << data[row][column] << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> const& other) {
    if (this == &other) return *this;
    delete[] data;
    delete[] values;
    rows = other.rows;
    cols = other.cols;
    data = new T *[rows];
    values = new T[rows * cols];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("memory is not allocated");
    }
    std::memcpy(values, other.values, sizeof(T) * other.rows * other.cols);
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& other) noexcept{
    if (this == &other) return *this;
    delete[] data;
    delete[] values;
    rows = other.rows;
    cols = other.cols;
    data = other.data;
    values = other.values;
    other.data = nullptr;
    other.values = nullptr;
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator+ (Matrix<T> const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw MatrixException ("sizes of the matrix are not equal");
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < sum_matrix.rows * sum_matrix.cols; cell++)
        sum_matrix.values[cell] += matrix.values[cell];
    return sum_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator+ (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> sum_matrix = *this;
    for (int cell = 0; cell < sum_matrix.rows * sum_matrix.cols; cell++)
        sum_matrix.values[cell] += number;
    return sum_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator- (Matrix<T> const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw MatrixException ("sizes of the matrix are not equal");
    }
    Matrix<T> sub_matrix = *this;
    for (int cell = 0; cell < sub_matrix.rows * sub_matrix.cols; cell++)
            sub_matrix.values[cell] -= matrix.values[cell];
    return sub_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator- (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> sub_matrix = *this;
    for (int cell = 0; cell < sub_matrix.rows * sub_matrix.cols; cell++)
        sub_matrix.values[cell] -= number;
    return sub_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T> const &matrix) const {
    if (cols != matrix.rows) {
        throw MatrixException ("wrong matrix sizes for multiplication");
    }
    Matrix<T> multiplied_matrix(cols, matrix.rows);
    for (int row = 0; row < multiplied_matrix.rows; row++)
        for (int column = 0; column < multiplied_matrix.cols; column++) {
            multiplied_matrix.data[row][column] = 0;
            for (int id = 0; id < cols; id++)
               multiplied_matrix.data[row][column] += data[row][id] * matrix.data[id][column];
        }
    return multiplied_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator* (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> multiplied_matrix = *this;
    for (int cell = 0; cell < multiplied_matrix.rows*multiplied_matrix.cols; cell++)
        multiplied_matrix.values[cell] *= number;
    return multiplied_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::minor_matrix(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    Matrix<T> minor(rows - 1, cols - 1);
    int row_shift = 0;
    for(int row = 0; row < minor.rows; row++) {
        if(excluded_row == row)
            row_shift += 1;
        int column_shift = 0;
        for (int column = 0; column < minor.cols; column++) {
            if(column == excluded_col) {
                column_shift += 1;
            }
            minor.data[row][column] = data[row + row_shift][column + column_shift];
        }
    }
    return minor;
}


template <typename T>
T Matrix<T>::determinant() const{
    if (rows != cols) {
        throw MatrixException ("matrix is not square");
    }
    if (rows == 0 || cols == 0) {
        throw MatrixException ("rows or cols is/are zero");
    }
    T determinant = 0;
    if (rows == 1) {
        determinant = data[0][0];
        return determinant;
    }
    T k = 1.0;
    for (int column = 0; column < cols; column++) {
        Matrix<T> minor = minor_matrix(0, column);
        determinant += k * data[0][column] * minor.determinant();
        k = -k;
    }
    return determinant;
}


template <typename T>
Matrix<T> Matrix<T>::transposition() const {
    Matrix<T> transposed_matrix(rows, cols);
    for(int row = 0; row < transposed_matrix.rows; row++)
        for(int column = 0; column < transposed_matrix.cols; column++)
            transposed_matrix.data[row][column] = data[column][row];
    return transposed_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::inversion() const {
    if (rows != cols) {
        throw MatrixException ("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException ("division by zero");
    }
    Matrix<T> matrix_buffer(this->transposition().rows, this->transposition().cols);
    if(matrix_buffer.rows == 1) {
        matrix_buffer = this->transposition();
    }
    else {
        for(int row = 0; row < this->transposition().rows; row++) {
            for(int column = 0; column < this->transposition().cols; column++) {
                Matrix<T> minor = this->transposition().minor_matrix(row, column);
                int k = ((row + column) % 2 == 0) ? 1 : -1;
                matrix_buffer.data[row][column] = k * minor.determinant();
            }
        }
    }
    Matrix<T> inverse_matrix = matrix_buffer * (1 / this->determinant());
    return inverse_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator/ (const Matrix<T> &matrix) const {
    if (rows != cols) {
        throw MatrixException ("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException ("division by zero");
    }
    Matrix<T> inverse_matrix = matrix.inversion();
    Matrix<T> inverse_multiplied_matrix(cols, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int column = 0; column < inverse_multiplied_matrix.cols; column++) {
            inverse_multiplied_matrix.data[row][column] = 0;
            for (int id = 0; id < cols; id++)
                inverse_multiplied_matrix.data[row][column] += data[row][id] * inverse_matrix.data[id][column];
        }
    return inverse_multiplied_matrix;
}


template <typename T>
Matrix<T> Matrix<T>::operator/ (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    if (std::abs(number) < EPSILON) {
        throw MatrixException ("division by zero");
    }
    Matrix<T> divided_matrix = *this;
    for (int cell = 0; cell < divided_matrix.rows * divided_matrix.cols; cell++)
        divided_matrix.values[cell] /= number;
    return divided_matrix;
}


template <typename T>
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


template <typename T>
Matrix<T> Matrix<T>::exp(const Matrix<T> &matrix, int STEPS) {
    if (matrix.rows != matrix.cols) {
        throw MatrixException("matrix is not square");
    }
    Matrix<T> exp_matrix(matrix.rows);
    T k = 1.0;
    for(int s = 1; s < STEPS; s++) {
        k *= s;
        exp_matrix = exp_matrix + matrix.power(s) / k;
    }
    return exp_matrix;
}


template class Matrix<double>;
template class Matrix<float>;