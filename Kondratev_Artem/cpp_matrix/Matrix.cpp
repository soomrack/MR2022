#include "Matrix.h"

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    values = nullptr;
    start = nullptr;
}

Matrix::Matrix(int input_rows, int input_cols) {
    Matrix_exception::positive_parameters(input_rows, input_cols);
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double [size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
}

Matrix::Matrix(int input_rows, int input_cols, double number) {
    Matrix_exception::positive_parameters(input_rows, input_cols);
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double [size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = number;
}

Matrix::Matrix(int input_rows, int input_cols, double const array[]) {
    Matrix_exception::positive_parameters(input_rows, input_cols);
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double [size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = array[cell];
}

Matrix::Matrix(int row_number) {
    Matrix_exception::positive_parameters(row_number, 1);
    rows = row_number;
    cols = rows;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double [size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            values[row][col] = (row == col) ? 1 : 0;
}

Matrix::~Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    delete values;
    delete start;
}

Matrix::Matrix(Matrix const &matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double[size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

Matrix::Matrix(Matrix const &&matrix) noexcept {
    rows = matrix.rows;
    cols = matrix.cols;
    size = matrix.size;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double[size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

[[maybe_unused]] int Matrix::get_rows(int print_flag) const {
    if (print_flag == 1)
        std::cout << "rows: " << rows;
    return rows;
}

[[maybe_unused]] int Matrix::get_cols(int print_flag) const {
    if (print_flag == 1)
        std::cout << "cols: " << cols;
    return cols;
}

int Matrix::get_size(int print_flag) const {
    if (print_flag == 1)
        std::cout << "size: " << size;
    return size;
}

[[maybe_unused]] void Matrix::output() const {
    if (values == nullptr)
    {}
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << std::scientific << std::setw(13) << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator = (Matrix const &matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double[size];
    Matrix_exception::is_start_null(start);
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

Matrix Matrix::operator + (Matrix const matrix) const {
    Matrix_exception::addition_check(rows, cols, matrix.rows, matrix.cols);
    Matrix sum_matrix(2, 2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + matrix.start[cell];
    return sum_matrix;
}

Matrix Matrix::operator + (double number) const {
    Matrix_exception::is_number_nan(number);
    Matrix sum_matrix(2, 2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + number;
    return sum_matrix;
}

Matrix Matrix::operator - (Matrix const matrix) const {
    Matrix_exception::subtraction_check(rows, cols, matrix.rows, matrix.cols);
    Matrix sum_matrix(2, 2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - matrix.start[cell];
    return sum_matrix;
}

Matrix Matrix::operator * (Matrix const matrix) const {
    Matrix_exception::multiplication_check(cols, matrix.rows);
    Matrix multiplied_matrix(cols, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.values[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.values[row][col] += values[row][k] * matrix.values[k][col];
        }
    return multiplied_matrix;
}

Matrix Matrix::operator * (double number) const {
    Matrix_exception::is_number_nan(number);
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.start[cell] = start[cell] * number;
    return operated_matrix;
}

Matrix Matrix::minor_init(int crossed_row, int crossed_col) const {
    Matrix_exception::positive_parameters(crossed_row, crossed_col);
    Matrix minor(rows - 1, cols - 1);
    int row_link = 0;
    for(int i = 0; i < minor.rows; i++) {
        if(crossed_row == i)
            row_link += 1;
        int col_link = 0;
        for (int j = 0; j < minor.cols; j++) {
            if(j == crossed_col)
                col_link += 1;
            minor.values[i][j] = values[i + row_link][j + col_link];
        }
    }
    return minor;
}

double Matrix::determinant() const{
    Matrix_exception::is_matrix_square(rows, cols);
    double determinant = 0;
    if(rows == 1) {
        determinant = values[0][0];
        return determinant;
    }
    int k = 1;
    for(int col = 0; col < cols; col++) {
        Matrix minor = minor_init(0, col);
        determinant += k * values[0][col] * minor.determinant();
        k = -k;
    }
    return determinant;
}

Matrix Matrix::transposition() const {
    int new_rows = cols;
    int new_cols = rows;
    Matrix transposed_matrix(new_rows, new_cols);
    for(int row = 0; row < transposed_matrix.rows; row++)
        for(int col = 0; col < transposed_matrix.cols; col++)
            transposed_matrix.values[row][col] = values[col][row];
    return transposed_matrix;
}

Matrix Matrix::minor_transformation(Matrix matrix) {
    Matrix_exception::is_matrix_square(matrix.rows, matrix.cols);
    Matrix transformed_matrix(matrix.rows, matrix.cols);
    if(matrix.rows == 1) {
        transformed_matrix = matrix;
        return transformed_matrix;
    }
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            Matrix minor = matrix.minor_init(row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            transformed_matrix.values[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}

Matrix Matrix::inversion() const {
    Matrix_exception::is_matrix_square(rows, cols);
    Matrix_exception::division_by_zero(this->determinant());
    Matrix transformed_matrix = minor_transformation(this->transposition());
    Matrix inverse_matrix = transformed_matrix * (1 / this->determinant());
    return inverse_matrix;
}

Matrix Matrix::operator / (Matrix matrix) const {
    Matrix_exception::is_matrix_square(rows, cols);
    Matrix_exception::division_by_zero(this->determinant());
    Matrix inverse_matrix = matrix.inversion();
    Matrix inverse_multiplied_matrix(cols, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int col = 0; col < inverse_multiplied_matrix.cols; col++) {
            inverse_multiplied_matrix.values[row][col] = 0;
            for (int k = 0; k < cols; k++)
                inverse_multiplied_matrix.values[row][col] += values[row][k] * inverse_matrix.values[k][col];
        }
    return inverse_multiplied_matrix;
}

Matrix Matrix::operator / (double number) const {
    Matrix_exception::is_number_nan(number);
    Matrix_exception::division_by_zero(number);
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.start[cell] = start[cell] / number;
    return operated_matrix;
}

Matrix Matrix::power(int power) const {
    Matrix matrix(rows, cols);
    for (int cell = 0; cell < size; cell++)
        matrix.start[cell] = this->start[cell];

    if (power == 0) {
        Matrix identity_matrix(matrix.rows);
        return identity_matrix;
    }
    if (power == 1) {
        return matrix;
    }
    if (power > 1) {
        Matrix powered_matrix = matrix;
        for (int k = 1; k < power; k++) {
            powered_matrix = powered_matrix * matrix;
        }
        return powered_matrix;
    }
    Matrix inverse_matrix = matrix.inversion();
    Matrix start_matrix = matrix.inversion();
    for (int k = 1; k < -power; k++) {
        inverse_matrix = inverse_matrix * start_matrix;
    }
    return inverse_matrix;
}

Matrix Matrix::exp(Matrix matrix) {
    Matrix exp_matrix(matrix.rows);
    double k = 1.0;
    for(int s = 1; s < 177; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}
