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
MatrixException ZERO_LENGTH(10, "rows / cols is zero");

void Matrix::number_filling(int size, double *values, double number) {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    for (int cell = 0; cell < size; cell++)
        values[cell] = number;
}

void Matrix::filling_from_vector(int size, double *values, std::vector<double> vector) {
    if (size != vector.size()) {
        throw WRONG_LENGTH;
    }
    for (int cell = 0; cell < size; cell++)
        values[cell] = vector[cell];
}

void Matrix::set_identity(double **data, int rows, int cols) {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            data[row][col] = (row == col) ? 1 : 0;
}

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    data = nullptr;
    values = nullptr;
}

Matrix::Matrix(int input_rows, int input_cols, FillType fill_type=DEFAULT, double number=0.0,
               const std::vector<double>& vector={}) {

    if (input_rows <= 0 || input_cols <= 0) {
        throw WRONG_PARAMETERS;
    }
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    data = new double *[rows];
    values = new double [size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    if (fill_type == NUMBER) {
        number_filling(size, values, number);
    }
    if (fill_type == VECTOR) {
        filling_from_vector(size, values, vector);
    }
    if (fill_type == IDENTITY) {
        set_identity(data, rows, cols);
    }
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    cols = other.cols;
    size = rows * cols;
    data = new double *[rows];
    values = new double[size];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++)
        data[row] = values + row * cols;
    for (int cell = 0; cell < size; cell++)
        values[cell] = other.values[cell];
}

Matrix::Matrix(Matrix &&other) noexcept {
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

Matrix::~Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    delete[] data;
    delete[] values;
}

int Matrix::get_rows() const {
    return rows;
}

int Matrix::get_cols() const {
    return cols;
}

int Matrix::get_size() const {
    return size;
}

double Matrix::get_value(int row, int col) const {
    if (row < 0 || col < 0) {
        throw WRONG_PARAMETERS;
    }
    return data[row][col];
}

void Matrix::output() const {
    if (data == nullptr || values == nullptr) {
        throw NULL_MEMORY;
    }
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << std::scientific << std::setw(13) << data[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator= (Matrix const &other) {
    if (this != &other) {
        delete[] data;
        delete[] values;
        rows = other.rows;
        cols = other.cols;
        size = rows * cols;
        data = new double *[rows];
        values = new double[size];
        if (data == nullptr || values == nullptr) {
            delete[] data;
            delete[] values;
            throw NULL_MEMORY;
        }
        for (int row = 0; row < rows; row++)
            data[row] = values + row * cols;

        std::memcpy(values, other.values, sizeof(double) * other.size);
    }
}

Matrix& Matrix::operator= (Matrix &&other) noexcept {
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
}

Matrix Matrix::operator+ (Matrix const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw ADDITION_ERROR;
    }
    Matrix sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += matrix.values[cell];
    return sum_matrix;
}

Matrix Matrix::operator+ (double number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    Matrix sum_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sum_matrix.values[cell] += number;
    return sum_matrix;
}

Matrix Matrix::operator- (Matrix const &matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw SUBTRACTION_ERROR;
    }
    Matrix sub_matrix = *this;
    for (int cell = 0; cell < size; cell++)
        sub_matrix.values[cell] -= matrix.values[cell];
    return sub_matrix;
}

Matrix Matrix::operator* (Matrix const &matrix) const {
    if (cols != matrix.rows) {
        throw MULTIPLICATION_ERROR;
    }
    Matrix multiplied_matrix(cols, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.data[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.data[row][col] += data[row][k] * matrix.data[k][col];
        }
    return multiplied_matrix;
}

Matrix Matrix::operator* (double number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    Matrix multiplied_matrix = *this;
    for(int cell = 0; cell < size; cell++)
        multiplied_matrix.values[cell] *= number;
    return multiplied_matrix;
}

Matrix Matrix::minor_init(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw WRONG_PARAMETERS;
    }
    Matrix minor(rows - 1, cols - 1);
    int row_shift = 0;
    for(int i = 0; i < minor.rows; i++) {
        if(excluded_row == i)
            row_shift += 1;
        int col_shift = 0;
        for (int j = 0; j < minor.cols; j++) {
            if(j == excluded_col) {
                col_shift += 1;
            }
            minor.data[i][j] = data[i + row_shift][j + col_shift];
        }
    }
    return minor;
}

double Matrix::determinant() const{
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (rows == 0 || cols == 0) {
        throw ZERO_LENGTH;
    }
    double determinant = 0;
    if (rows == 1) {
        determinant = data[0][0];
        return determinant;
    }
    float k = 1.0;
    for (int col = 0; col < cols; col++) {
        Matrix minor = minor_init(0, col);
        determinant += k * data[0][col] * minor.determinant();
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
            transposed_matrix.data[row][col] = data[col][row];
    return transposed_matrix;
}

Matrix Matrix::minor_transformation(const Matrix &matrix) {
    if (matrix.rows != matrix.cols) {
        throw NOT_SQUARE;
    }
    Matrix transformed_matrix(matrix.rows, matrix.cols);
    if(matrix.rows == 1) {
        transformed_matrix = matrix;
        return transformed_matrix;
    }
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            Matrix minor = matrix.minor_init(row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            transformed_matrix.data[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}

Matrix Matrix::inversion() const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix transformed_matrix = minor_transformation(this->transposition());
    Matrix inverse_matrix = transformed_matrix * (1 / this->determinant());
    return inverse_matrix;
}

Matrix Matrix::operator/ (const Matrix &matrix) const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix inverse_matrix = matrix.inversion();
    Matrix inverse_multiplied_matrix(cols, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int col = 0; col < inverse_multiplied_matrix.cols; col++) {
            inverse_multiplied_matrix.data[row][col] = 0;
            for (int k = 0; k < cols; k++)
                inverse_multiplied_matrix.data[row][col] += data[row][k] * inverse_matrix.data[k][col];
        }
    return inverse_multiplied_matrix;
}

Matrix Matrix::operator/ (double number) const {
    if (std::isnan(number)) {
        throw NAN_NUMBER;
    }
    if (std::abs(number) < EPSILON) {
        throw DIVISION_BY_ZERO;
    }
    Matrix divided_matrix = *this;
    for(int cell = 0; cell < size; cell++)
        divided_matrix.values[cell] /= number;
    return divided_matrix;
}

Matrix Matrix::power(int power) const {
    if (rows != cols) {
        throw NOT_SQUARE;
    }
    if (power == 0) {
        Matrix identity_matrix(this->rows, this->cols, NUMBER, 1);
        return identity_matrix;
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

Matrix Matrix::exp(const Matrix &matrix, int STEPS) {
    if (matrix.rows != matrix.cols) {
        throw NOT_SQUARE;
    }
    Matrix exp_matrix(matrix.rows, matrix.cols, IDENTITY, 0.0);
    double k = 1.0;
    for(int s = 1; s < STEPS; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}
