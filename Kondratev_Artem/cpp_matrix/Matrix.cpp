#include "Matrix.h"

MatrixException negative_parameters(1, "matrix parameters are less than zero");
MatrixException memory_is_null(2, "memory is not allocated");
MatrixException addition_error(3, "wrong matrix sizes for addition");
MatrixException subtraction_error(4, "wrong matrix sizes for subtraction");
MatrixException number_is_nan(5, "number is NAN");
MatrixException multiplication_error(6, "wrong matrix sizes for multiplication");
MatrixException division_by_zero(7, "division_by_zero");
MatrixException matrix_is_not_square(8, "matrix is not square");
MatrixException wrong_length(9, "length of vector is wrong");

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    values = nullptr;
    start = nullptr;
}

Matrix::Matrix(int input_rows, int input_cols) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double [size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
}

Matrix::Matrix(int input_rows, int input_cols, double number) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    if (std::isnan(number))
        throw number_is_nan;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double [size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = number;
}

Matrix::Matrix(int input_rows, int input_cols, std::vector<double> vector) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    if (size != vector.size())
        throw wrong_length;
    values = new double *[rows];
    start = new double [size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int cell = 0; cell < size; cell++)
        start[cell] = vector[cell];
}

Matrix::Matrix(int row_number) {
    if (row_number < 0) {
        throw negative_parameters;
    }
    rows = row_number;
    cols = rows;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < cols; col++)
            values[row][col] = (row == col) ? 1 : 0;
}

Matrix::Matrix(Matrix const &matrix) {
    //delete[] values;
    //delete[] start;
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

Matrix::Matrix(Matrix &&matrix) noexcept {
    //delete[] values;
    //delete[] start;
    rows = matrix.rows;
    cols = matrix.cols;
    size = matrix.size;
    values = matrix.values;
    start = matrix.start;
    matrix.values = nullptr;
    matrix.start = nullptr;
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
}

Matrix::~Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    delete[] values;
    delete[] start;
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

void Matrix::output() const {
    if (values == nullptr || start == nullptr)
        throw memory_is_null;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << std::scientific << std::setw(13) << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator= (Matrix const &matrix) {
    delete[] values;
    delete[] start;
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

Matrix& Matrix::operator= (Matrix const &&matrix) noexcept {
    delete[] values;
    delete[] start;
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    if (values == nullptr || start == nullptr) {
        delete[] values;
        delete[] start;
        throw memory_is_null;
    }
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}

Matrix Matrix::operator+ (Matrix const matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw addition_error;
    }
    Matrix sum_matrix(rows, cols);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + matrix.start[cell];
    return sum_matrix;
}

Matrix Matrix::operator+ (double number) const {
    if (std::isnan(number)) {
        throw number_is_nan;
    }
    Matrix sum_matrix(2, 2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + number;
    return sum_matrix;
}

Matrix Matrix::operator- (Matrix const matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw subtraction_error;
    }
    Matrix sum_matrix(rows, cols);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - matrix.start[cell];
    return sum_matrix;
}

Matrix Matrix::operator* (Matrix const matrix) const {
    if (cols != matrix.rows) {
        throw multiplication_error;
    }
    Matrix multiplied_matrix(cols, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.values[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.values[row][col] += values[row][k] * matrix.values[k][col];
        }
    return multiplied_matrix;
}

Matrix Matrix::operator* (double number) const {
    if (std::isnan(number)) {
        throw number_is_nan;
    }
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.start[cell] = start[cell] * number;
    return operated_matrix;
}

Matrix Matrix::minor_init(int excluded_row, int excluded_col) const {
    if (excluded_row < 0 || excluded_col < 0) {
        throw negative_parameters;
    }
    Matrix minor(rows - 1, cols - 1);
    int row_link = 0;  //shift
    for(int i = 0; i < minor.rows; i++) {
        if(excluded_row == i)
            row_link += 1;
        int col_link = 0;
        for (int j = 0; j < minor.cols; j++) {
            if(j == excluded_col)
                col_link += 1;
            minor.values[i][j] = values[i + row_link][j + col_link];
        }
    }
    return minor;
}

double Matrix::determinant() const{
    if (rows != cols) {
        throw matrix_is_not_square;
    }
    double determinant = 0;
    if(rows == 1) {
        determinant = values[0][0];
        return determinant;
    }
    float k = 1.0;
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
    if (matrix.rows != matrix.cols) {
        throw matrix_is_not_square;
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
            transformed_matrix.values[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}

Matrix Matrix::inversion() const {
    if (rows != cols) {
        throw matrix_is_not_square;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw division_by_zero;
    }
    Matrix transformed_matrix = minor_transformation(this->transposition());
    Matrix inverse_matrix = transformed_matrix * (1 / this->determinant());
    return inverse_matrix;
}

Matrix Matrix::operator/ (Matrix matrix) const {
    if (rows != cols) {
        throw matrix_is_not_square;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw division_by_zero;
    }
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

Matrix Matrix::operator/ (double number) const {
    if (std::isnan(number)) {
        throw number_is_nan;
    }
    if (std::abs(number) < EPSILON) {
        throw division_by_zero;
    }
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.start[cell] = start[cell] / number;
    return operated_matrix;
}

Matrix Matrix::power(int power) const {
    if (rows != cols) {
        throw matrix_is_not_square;
    }

    Matrix origin(rows, cols);  // 
    for (int cell = 0; cell < size; cell++)
        origin.start[cell] = this->start[cell];

    if (power == 0) {
        Matrix identity_matrix(origin.rows);
        return identity_matrix;
    }
    if (power == 1) {
        return origin;
    }
    if (power > 1) {
        Matrix powered_matrix = origin;
        for (int k = 1; k < power; k++) {
            powered_matrix = powered_matrix * origin;
        }
        return powered_matrix;
    }
    Matrix powered_matrix = origin.inversion();  // power < 0
    origin = origin.inversion();
    for (int k = 1; k < -power; k++) {
        powered_matrix = powered_matrix * origin;
    }
    return powered_matrix;
}

Matrix Matrix::exp(Matrix matrix) {  //steps
    if (matrix.rows != matrix.cols) {
        throw matrix_is_not_square;
    }
    Matrix exp_matrix(matrix.rows);
    double k = 1.0;
    for(int s = 1; s < EXP_STEP; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}
