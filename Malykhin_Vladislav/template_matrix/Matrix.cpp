#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix() noexcept {
    rows = 0;
    columns = 0;
}

template <typename T>
Matrix<T>::Matrix(int input_rows, int input_columns) {
    if(input_rows <= 0 || input_columns <= 0) {
        throw MatrixException("matrix parameters are less than zero");
    }
    rows = input_rows;
    columns = input_columns;
    cells.reserve(rows);
    std::vector <T> column_vector;
    column_vector.reserve(columns);
    column_vector.resize(columns,0);
    cells.resize(rows,column_vector);
}

template <typename T>
Matrix<T>::Matrix(int input_rows, int input_columns,T number) {
    if(input_rows <= 0 || input_columns <= 0) {
          throw MatrixException("matrix parameters are less than zero");
    }
    rows = input_rows;
    columns = input_columns;
    cells.reserve(rows);
    std::vector <T> column_vector;
    column_vector.reserve(columns);
    column_vector.resize(columns,number);
    cells.resize(rows, column_vector);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &other) noexcept {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells;
}


template<typename T>
Matrix<T>::Matrix(int input_rows, int input_columns, const std::vector<T> &vector) : Matrix(input_rows, input_columns){
    if (rows * columns != vector.size()) {
        throw MatrixException("length of vector is wrong");
    }
       for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {
            cells[row][column] = vector[row * columns + column];
        }
    }
}


template <typename T>
void Matrix<T>::set_identity() {
    if (rows != columns) {
        throw MatrixException ("matrix is not square");
    }
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < columns; col++)
            cells[row][col] = (row == col) ? 1 : 0;
}

template <typename T>
int Matrix<T>::get_rows() const {
    return rows;
}

template <typename T>
int Matrix<T>::get_columns() const {
    return columns;
}

template <typename T>
int Matrix<T>::get_size() const {
    return columns * rows;
}

template <typename T>
T Matrix<T>::get_cell(int row, int column) const {
    if (row < 0 || column < 0) {
        throw MatrixException ("matrix parameters are less than zero");
    }
    return cells[row][column];
}

template <typename T>
void Matrix<T>::print() const {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++)
            std::cout << std::scientific << std::setw(13) << cells[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> const &other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        cells = other.cells;
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T> &&other) noexcept {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        this->cells = other.cells;
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (Matrix<T> const &matrix) const {
    if (rows != matrix.rows || columns != matrix.columns) {
        throw MatrixException ("sizes of the matrix are not equal");
    }
    Matrix<T> sum_matrix = *this;
    for (int row = 0; row < matrix.rows; row++)
        for (int column = 0; column < matrix.rows; column++)
            sum_matrix.cells[row][column] += matrix.cells[row][column];
    return sum_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator+ (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> sum_matrix = *this;
    for (int row = 0; row < sum_matrix.rows; row++)
        for (int column = 0; column < sum_matrix.rows; column++)
            sum_matrix.cells[row][column] += number;
    return sum_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (Matrix<T> const &matrix) const {
    if (rows != matrix.rows || columns != matrix.columns) {
        throw MatrixException ("sizes of the matrix are not equal");
    }
    Matrix<T> sum_matrix = *this;
    for (int row = 0; row < matrix.rows; row++)
        for (int column = 0; column < matrix.rows; column++)
            sum_matrix.cells[row][column] -= matrix.cells[row][column];
    return sum_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> sum_matrix = *this;
    for (int row = 0; row < sum_matrix.rows; row++)
        for (int column = 0; column < sum_matrix.rows; column++)
            sum_matrix.cells[row][column] -= number;
    return sum_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (Matrix<T> const &matrix) const {
    if (columns != matrix.rows) {
        throw MatrixException ("wrong matrix sizes for multiplication");
    }
    Matrix<T> multiplied_matrix(columns, matrix.rows);
    for (int row = 0; row < multiplied_matrix.rows; row++)
        for (int column = 0; column < multiplied_matrix.columns; column++) {
            for (int counter = 0; counter < columns; counter++)
               multiplied_matrix.cells[row][column] += cells[row][counter] * matrix.cells[counter][column];

        }
    return multiplied_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (T number) const {
    if (std::isnan(number)) {
        throw MatrixException ("input value is not a number");
    }
    Matrix<T> multiplied_matrix = *this;
    for (int row = 0; row < multiplied_matrix.rows; row++)
        for (int column = 0; column < multiplied_matrix.rows; column++)
            multiplied_matrix.cells[row][column] *= number;
    return multiplied_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::minor_matrix(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw MatrixException ("matrix parameters are less than zero");
    }
    Matrix<T> minor(rows - 1, columns - 1);
    int row_shift = 0;
    for(int i = 0; i < minor.rows; i++) {
        if(excluded_row == i)
            row_shift += 1;
        int column_shift = 0;
        for (int j = 0; j < minor.columns; j++) {
            if(j == excluded_col) {
                column_shift += 1;
            }
            minor.cells[i][j] = cells[i + row_shift][j + column_shift];
        }
    }
    return minor;
}

template <typename T>
T Matrix<T>::determinant() const{
    if (rows != columns) {
        throw MatrixException ("matrix is not square");
    }
    if (rows == 0 || columns == 0) {
        throw MatrixException ("rows or cols is/are zero");
    }
    T determinant = 0;
    if (rows == 1) {
        determinant = cells[0][0];
        return determinant;
    }
    T k = 1.0;
    for (int column = 0; column < columns; column++) {
        Matrix<T> minor = minor_matrix(0, column);
        determinant += k * cells[0][column] * minor.determinant();
        k = -k;
    }
    return determinant;
}

template <typename T>
Matrix<T> Matrix<T>::transposition() const {
    Matrix<T> transposed_matrix = *this;
    for(int row = 0; row < transposed_matrix.rows; row++)
        for(int column = 0; column < transposed_matrix.columns; column++)
            transposed_matrix.cells[row][column] = cells[column][row];
    return transposed_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::inversion() const {
    if (rows != columns) {
        throw MatrixException ("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException ("division by zero");
    }
    Matrix<T> matrix_buffer(this->transposition().rows, this->transposition().columns);
    if(matrix_buffer.rows == 1) {
        matrix_buffer = this->transposition();
    }
    else {
        for(int row = 0; row < this->transposition().rows; row++) {
            for(int column = 0; column < this->transposition().columns; column++) {
                Matrix<T> minor = this->transposition().minor_matrix(row, column);
                int k = ((row + column) % 2 == 0) ? 1 : -1;
                matrix_buffer.cells[row][column] = k * minor.determinant();
            }
        }
    }
    Matrix<T> inverse_matrix = matrix_buffer * (1 / this->determinant());
    return inverse_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator/ (const Matrix<T> &matrix) const {
    if (rows != columns) {
        throw MatrixException ("matrix is not square");
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw MatrixException ("division by zero");
    }
    Matrix<T> inverse_matrix = matrix.inversion();
    Matrix<T> inverse_multiplied_matrix(columns, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int column = 0; column < inverse_multiplied_matrix.columns; column++) {
            inverse_multiplied_matrix.cells[row][column] = 0;
            for (int counter = 0; counter < columns; counter++)
                inverse_multiplied_matrix.cells[row][column] += cells[row][counter] * inverse_matrix.cells[counter][column];
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
    for (int row = 0; row < divided_matrix.rows; row++)
        for (int column = 0; column < divided_matrix.rows; column++)
            divided_matrix.cells[row][column] /= number;
    return divided_matrix;
}

template <typename T>
Matrix<T> Matrix<T>::power(int power) const {
    if (rows != columns) {
        throw MatrixException ("matrix is not square");
    }
    if (power == 0) {
        Matrix<T> powered_matrix(this->rows, this->columns);
        powered_matrix.set_identity();
        return powered_matrix;
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
    if (matrix.rows != matrix.columns) {
        throw MatrixException ("matrix is not square");
    }
    Matrix<T> exp_matrix(matrix.rows, matrix.columns);
    exp_matrix.set_identity();
    T k = 1.0;
    for(int s = 1; s < STEPS; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}

template
class Matrix<double>;

template
class Matrix<float>;