//
// Created by User on 05.12.2022.
//

#include "Matrix.h"


Matrix::Matrix() noexcept {
    rows = 0;
    columns = 0;
}

Matrix::Matrix(int input_rows, int input_columns, double number) {
    if (input_rows <= 0 || input_columns <= 0) {
        //  throw WRONG_PARAMETERS;
    }
    rows = input_rows;
    columns = input_columns;
    if (not std::isnan(number)) {
        for (int row = 0; row < rows; row++)
            for (int column = 0; column < columns; column++)
                cells[row][column] = number;
    }
}

Matrix::Matrix(const Matrix &other) noexcept {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells;
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells; //  добавить проверку на nullptr
}


void Matrix::vector_fill(std::vector<double> vector) {
    if (rows*columns != vector.size()) {
      //  throw WRONG_LENGTH;
    }
    for(unsigned int row = 0; row < rows; row++)
        for (unsigned int col = 0; col < columns; ++col) {
           cells[row][col] = vector[col+row*(rows - 1)];
        }
}

void Matrix::vector_fill(const std::vector<std::vector<double>>& vector){
    if (cells.size() != vector.size()) {
        //  throw WRONG_LENGTH;
    }
    cells = vector;
}

void Matrix::set_identity() {
    if (rows != columns) {
       // throw NOT_SQUARE;
    }
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < columns; col++)
            cells[row][col] = (row == col) ? 1 : 0;
}


unsigned int Matrix::get_rows() const {
    return rows;
}


unsigned int Matrix::get_columns() const {
    return columns;
}


unsigned int Matrix::get_size() const {
    return columns * rows;
}


double Matrix::get_cell(int row, int column) const {
    if (row < 0 || column < 0) {
       // throw WRONG_PARAMETERS;
    }
    return cells[row][column];
}


void Matrix::output() const {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++)
            std::cout << std::scientific << std::setw(13) << cells[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator= (Matrix const &other) {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        cells = other.cells;
    }
    return *this;
}

Matrix& Matrix::operator= (Matrix &&other) noexcept {
    if (this != &other) {
        rows = other.rows;
        columns = other.columns;
        this->cells = other.cells;
    }
    return *this;
}

Matrix Matrix::operator+ (Matrix const &matrix) const {
    if (rows != matrix.rows || columns != matrix.columns) {
        //throw ADDITION_ERROR;
    }
    Matrix sum_matrix = *this;
    for (int row = 0; row < matrix.rows; row++)
        for (int column = 0; column < matrix.rows; column++)
            sum_matrix.cells[row][column] += matrix.cells[row][column];
    return sum_matrix;
}


Matrix Matrix::operator+ (double number) const {
    if (std::isnan(number)) {
       // throw NAN_NUMBER;
    }
    Matrix sum_matrix = *this;
    for (int row = 0; row < sum_matrix.rows; row++)
        for (int column = 0; column < sum_matrix.rows; column++)
            sum_matrix.cells[row][column] += number;
    return sum_matrix;
}

Matrix Matrix::operator- (Matrix const &matrix) const {
    if (rows != matrix.rows || columns != matrix.columns) {
        //throw ADDITION_ERROR;
    }
    Matrix sum_matrix = *this;
    for (int row = 0; row < matrix.rows; row++)
        for (int column = 0; column < matrix.rows; column++)
            sum_matrix.cells[row][column] -= matrix.cells[row][column];
    return sum_matrix;
}


Matrix Matrix::operator- (double number) const {
    if (std::isnan(number)) {
        // throw NAN_NUMBER;
    }
    Matrix sum_matrix = *this;
    for (int row = 0; row < sum_matrix.rows; row++)
        for (int column = 0; column < sum_matrix.rows; column++)
            sum_matrix.cells[row][column] -= number;
    return sum_matrix;
}

Matrix Matrix::operator* (Matrix const &matrix) const {
    if (columns != matrix.rows) {
        //throw MULTIPLICATION_ERROR;
    }
    Matrix multiplied_matrix(columns, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int column = 0; column < multiplied_matrix.columns; column++) {
            multiplied_matrix.cells[row][column] = 0;
            for (int counter = 0; counter < column; counter++)
                multiplied_matrix.cells[row][column] += cells[row][counter] * matrix.cells[counter][column];
        }
    return multiplied_matrix;
}


Matrix Matrix::operator* (double number) const {
    if (std::isnan(number)) {
       // throw NAN_NUMBER;
    }
    Matrix multiplied_matrix = *this;
    for (int row = 0; row < multiplied_matrix.rows; row++)
        for (int column = 0; column < multiplied_matrix.rows; column++)
            multiplied_matrix.cells[row][column] *= number;
    return multiplied_matrix;
}


Matrix Matrix::minor_matrix(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
       // throw WRONG_PARAMETERS;
    }
    Matrix minor(rows - 1, columns - 1);
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


double Matrix::determinant() const{
    if (rows != columns) {
        //throw NOT_SQUARE;
    }
    if (rows == 0 || columns == 0) {
        //throw ZERO_LENGTH;
    }
    double determinant = 0;
    if (rows == 1) {
        determinant = cells[0][0];
        return determinant;
    }
    float k = 1.0;
    for (int column = 0; column < columns; column++) {
        Matrix minor = minor_matrix(0, column);
        determinant += k * cells[0][column] * minor.determinant();
        k = -k;
    }
    return determinant;
}


Matrix Matrix::transposition() const {
    Matrix transposed_matrix(columns, rows);
    for(int row = 0; row < transposed_matrix.rows; row++)
        for(int column = 0; column < transposed_matrix.columns; column++)
            transposed_matrix.cells[row][columns] = cells[columns][row];
    return transposed_matrix;
}


Matrix Matrix::inversion() const {
    if (rows != columns) {
        //throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
       // throw DIVISION_BY_ZERO;
    }
    Matrix matrix_buffer(this->transposition().rows, this->transposition().columns);
    if(matrix_buffer.rows == 1) {
        matrix_buffer = this->transposition();
    }
    else {
        for(int row = 0; row < this->transposition().rows; row++) {
            for(int column = 0; column < this->transposition().columns; column++) {
                Matrix minor = this->transposition().minor_matrix(row, column);
                int k = ((row + column) % 2 == 0) ? 1 : -1;
                matrix_buffer.cells[row][column] = k * minor.determinant();
            }
        }
    }
    Matrix inverse_matrix = matrix_buffer * (1 / this->determinant());
    return inverse_matrix;
}


Matrix Matrix::operator/ (const Matrix &matrix) const {
    if (rows != columns) {
        //throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        //throw DIVISION_BY_ZERO;
    }
    Matrix inverse_matrix = matrix.inversion();
    Matrix inverse_multiplied_matrix(columns, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int column = 0; column < inverse_multiplied_matrix.columns; column++) {
            inverse_multiplied_matrix.cells[row][column] = 0;
            for (int counter = 0; counter < columns; counter++)
                inverse_multiplied_matrix.cells[row][column] += cells[row][counter] * inverse_matrix.cells[counter][column];
        }
    return inverse_multiplied_matrix;
}


Matrix Matrix::operator/ (double number) const {
    if (std::isnan(number)) {
       // throw NAN_NUMBER;
    }
    if (std::abs(number) < EPSILON) {
       // throw DIVISION_BY_ZERO;
    }
    Matrix divided_matrix = *this;
    for (int row = 0; row < divided_matrix.rows; row++)
        for (int column = 0; column < divided_matrix.rows; column++)
            divided_matrix.cells[row][column] /= number;
    return divided_matrix;
}

Matrix Matrix::power(int power) const {
    if (rows != columns) {
       // throw NOT_SQUARE;
    }
    if (power == 0) {
        Matrix powered_matrix(this->rows, this->columns);
        powered_matrix.set_identity();
        return powered_matrix;
    }
    if (power == 1) {
        return *this;
    }
    Matrix powered_matrix;
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

Matrix Matrix::exp(const Matrix& matrix, int STEPS) {
    if (matrix.rows != matrix.columns) {
      //  throw NOT_SQUARE;
    }
    Matrix exp_matrix(matrix.rows, matrix.columns);
    exp_matrix.set_identity();
    double k = 1.0;
    for(int s = 1; s < STEPS; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}