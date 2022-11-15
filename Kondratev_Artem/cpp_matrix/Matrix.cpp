#include "Matrix.h"

MatrixException negative_parameters(1, "matrix parameters are less than zero");
MatrixException null_memory(2, "memory is not allocated");
MatrixException addition_error(3, "wrong matrix sizes for addition");
MatrixException subtraction_error(4, "wrong matrix sizes for subtraction");
MatrixException nan_number(5, "number is NAN");
MatrixException multiplication_error(6, "wrong matrix sizes for multiplication");
MatrixException division_by_zero(7, "division_by_zero");
MatrixException not_square(8, "matrix is not square");
MatrixException wrong_length(9, "length of vector is wrong");

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    size = 0;
    pointers = nullptr;
    data = nullptr;
}

Matrix::Matrix(int input_rows, int input_cols, int identity_flag=0) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    pointers = new double *[rows];
    data = new double [size];
    if (pointers == nullptr || data == nullptr) {
        delete[] pointers;
        delete[] data;
        throw null_memory;
    }
    for (int row = 0; row < rows; row++)
        pointers[row] = data + row * cols;
    if (identity_flag == 1) {
        if (rows != cols) {
            throw not_square;
        }
        for (int row = 0; row < rows; row++)
            for (int col = 0; col < cols; col++)
                pointers[row][col] = (row == col) ? 1 : 0;
    }
}

Matrix::Matrix(int input_rows, int input_cols, double number) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    if (std::isnan(number))
        throw nan_number;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    pointers = new double *[rows];
    data = new double [size];
    if (pointers == nullptr || data == nullptr) {
        delete[] pointers;
        delete[] data;
        throw null_memory;
    }
    for (int row = 0; row < rows; row++)
        pointers[row] = data + row * cols;
    for (int cell = 0; cell < size; cell++)
        data[cell] = number;
}

Matrix::Matrix(int input_rows, int input_cols, std::vector<double> vector) {
    if (input_rows < 0 || input_cols < 0)
        throw negative_parameters;
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    if (size != vector.size())
        throw wrong_length;
    pointers = new double *[rows];
    data = new double [size];
    for (int row = 0; row < rows; row++)
        pointers[row] = data + row * cols;
    if (pointers == nullptr || data == nullptr) {
        delete[] pointers;
        delete[] data;
        throw null_memory;
    }
    for (int cell = 0; cell < size; cell++)
        data[cell] = vector[cell];
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    cols = other.cols;
    size = rows * cols;
    pointers = new double *[rows];
    data = new double[size];
    if (pointers == nullptr || data == nullptr) {
        delete[] pointers;
        delete[] data;
        throw null_memory;
    }
    for (int row = 0; row < rows; row++)
        pointers[row] = data + row * cols;
    for (int cell = 0; cell < size; cell++)
        data[cell] = other.data[cell];
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    cols = other.cols;
    size = other.size;
    pointers = other.pointers;
    data = other.data;
    if (pointers == nullptr || data == nullptr) {
        delete[] pointers;
        delete[] data;
        throw null_memory;
    }
    other.pointers = nullptr;
    other.data = nullptr;
    for (int row = 0; row < rows; row++)
        pointers[row] = data + row * cols;
}

Matrix::~Matrix() {
    rows = NAN;
    cols = NAN;
    size = NAN;
    delete[] pointers;
    delete[] data;
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
    if (pointers == nullptr || data == nullptr)
        throw null_memory;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << std::scientific << std::setw(13) << pointers[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}

Matrix& Matrix::operator= (Matrix const &other) {
    if (this != &other) {
        delete[] pointers;
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        size = rows * cols;
        pointers = new double *[rows];
        data = new double[size];
        if (pointers == nullptr || data == nullptr) {
            delete[] pointers;
            delete[] data;
            throw null_memory;
        }
        for (int row = 0; row < rows; row++)
            pointers[row] = data + row * cols;
        for (int cell = 0; cell < size; cell++)
            data[cell] = other.data[cell];
    }
}

Matrix& Matrix::operator= (Matrix &&other) noexcept {
    if (this != &other) {
        delete[] pointers;
        delete[] data;
        rows = other.rows;
        cols = other.cols;
        size = rows * cols;
        pointers = other.pointers;
        data = other.data;
        if (pointers == nullptr || data == nullptr) {
            delete[] pointers;
            delete[] data;
            throw null_memory;
        }
        other.pointers = nullptr;
        other.data = nullptr;
        for (int row = 0; row < rows; row++)
            pointers[row] = data + row * cols;
    }
}

Matrix Matrix::operator+ (Matrix const matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw addition_error;
    }
    Matrix sum_matrix(rows, cols);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.data[cell] = data[cell] + matrix.data[cell];
    return sum_matrix;
}

Matrix Matrix::operator+ (double number) const {
    if (std::isnan(number)) {
        throw nan_number;
    }
    Matrix sum_matrix(2, 2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.data[cell] = data[cell] + number;
    return sum_matrix;
}

Matrix Matrix::operator- (Matrix const matrix) const {
    if (rows != matrix.rows || cols != matrix.cols) {
        throw subtraction_error;
    }
    Matrix sum_matrix(rows, cols);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.data[cell] = data[cell] - matrix.data[cell];
    return sum_matrix;
}

Matrix Matrix::operator* (Matrix const matrix) const {
    if (cols != matrix.rows) {
        throw multiplication_error;
    }
    Matrix multiplied_matrix(cols, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.pointers[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.pointers[row][col] += pointers[row][k] * matrix.pointers[k][col];
        }
    return multiplied_matrix;
}

Matrix Matrix::operator* (double number) const {
    if (std::isnan(number)) {
        throw nan_number;
    }
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.data[cell] = data[cell] * number;
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
            minor.pointers[i][j] = pointers[i + row_link][j + col_link];
        }
    }
    return minor;
}

double Matrix::determinant() const{
    if (rows != cols) {
        throw not_square;
    }
    double determinant = 0;
    if(rows == 1) {
        determinant = pointers[0][0];
        return determinant;
    }
    float k = 1.0;
    for(int col = 0; col < cols; col++) {
        Matrix minor = minor_init(0, col);
        determinant += k * pointers[0][col] * minor.determinant();
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
            transposed_matrix.pointers[row][col] = pointers[col][row];
    return transposed_matrix;
}

Matrix Matrix::minor_transformation(Matrix matrix) {
    if (matrix.rows != matrix.cols) {
        throw not_square;
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
            transformed_matrix.pointers[row][col] = k * minor.determinant();
        }
    }
    return transformed_matrix;
}

Matrix Matrix::inversion() const {
    if (rows != cols) {
        throw not_square;
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
        throw not_square;
    }
    if (std::abs(this->determinant()) < EPSILON) {
        throw division_by_zero;
    }
    Matrix inverse_matrix = matrix.inversion();
    Matrix inverse_multiplied_matrix(cols, inverse_matrix.rows);
    for(int row = 0; row < inverse_multiplied_matrix.rows; row++)
        for(int col = 0; col < inverse_multiplied_matrix.cols; col++) {
            inverse_multiplied_matrix.pointers[row][col] = 0;
            for (int k = 0; k < cols; k++)
                inverse_multiplied_matrix.pointers[row][col] += pointers[row][k] * inverse_matrix.pointers[k][col];
        }
    return inverse_multiplied_matrix;
}

Matrix Matrix::operator/ (double number) const {
    if (std::isnan(number)) {
        throw nan_number;
    }
    if (std::abs(number) < EPSILON) {
        throw division_by_zero;
    }
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.data[cell] = data[cell] / number;
    return operated_matrix;
}

Matrix Matrix::power(int power) const {
    if (rows != cols) {
        throw not_square;
    }

    Matrix origin(rows, cols);  // 
    for (int cell = 0; cell < size; cell++)
        origin.data[cell] = this->data[cell];

    if (power == 0) {
        Matrix identity_matrix(origin.rows, origin.cols, 1);
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
        throw not_square;
    }
    Matrix exp_matrix(matrix.rows, matrix.cols, 1);
    double k = 1.0;
    for(int s = 1; s < EXP_STEP; s++) {
        k /= s;
        exp_matrix = exp_matrix + matrix.power(s) * k;
    }
    return exp_matrix;
}
