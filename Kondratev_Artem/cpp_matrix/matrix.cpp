#include <iostream>
#include <cmath>
#include <iomanip>
#include <exception>


#define EPSILON 0.000001


class Matrix {
private:
    int rows{};
    int cols;
    int size;
public:
    double **values;
    double *start;

    Matrix(int input_rows, int input_cols);
    Matrix(int input_rows, int input_cols, double number);  //  number filled matrix
    explicit Matrix(int row_number);  //  identity matrix
    Matrix(int input_rows, int input_cols, double const array[]);  // filling from array
    ~Matrix();
    Matrix(Matrix const &matrix);
    //Matrix(Matrix const &&matrix) noexcept;

    Matrix &operator = (Matrix const &matrix);
    Matrix operator + (Matrix matrix) const;
    Matrix operator + (double number) const;
    Matrix operator - (Matrix matrix) const;
    Matrix operator * (Matrix matrix) const;
    Matrix operator * (double number) const;
    Matrix operator / (Matrix matrix) const;
    Matrix operator / (double number) const;

    unsigned int get_rows(int print_flag) const;
    unsigned int get_cols(int print_flag) const;
    unsigned int get_size(int print_flag) const;
    static Matrix error();
    void output() const;
    Matrix minor_init(int crossed_row, int crossed_col) const;
    double determinant() const;
    Matrix transposition() const;
    static Matrix minor_transformation(Matrix matrix);
    Matrix inversion() const;
    Matrix power(int power) const;
    static Matrix exp(Matrix matrix);
};


class Matrix_exception: public std::exception {
private:
    inline static std::string msg;
    inline static int ex_number;
public:
    Matrix_exception() = default;
    ~Matrix_exception() override = default;
    static std::string get_msg() { return msg;};
    static int get_ex_number() {return ex_number;};
    static void positive_parameters(int input_rows, int input_cols);
    static void is_values_null(double **values);
    static void are_sizes_equal(int rows1, int cols1, int rows2, int cols2);
    static void is_number_nan(double number);
};


void Matrix_exception::positive_parameters(int input_rows, int input_cols) {
    if (input_rows < 0 || input_cols < 0) {
        Matrix_exception::ex_number = 1;
        Matrix_exception::msg = "matrix parameters are less than zero";
        throw get_ex_number();
    }
}

void Matrix_exception::is_values_null(double **values) {
    if (nullptr == values) {
        Matrix_exception::ex_number = 2;
        Matrix_exception::msg = "values: memory is not allocated";
        throw get_ex_number();
    }
}


void Matrix_exception::are_sizes_equal(int rows1, int cols1, int rows2, int cols2) {
    if (rows1 != rows2 || cols1 != cols2) {
        Matrix_exception::ex_number = 3;
        Matrix_exception::msg = "matrices sizes are not equal";
        throw get_ex_number();
    }
}

void Matrix_exception::is_number_nan(double number) {
    if (number != number) {
        Matrix_exception::ex_number = 4;
        Matrix_exception::msg = "number is NaN";
        throw get_ex_number();
    }
}


Matrix::Matrix(int input_rows, int input_cols) {
    Matrix_exception::positive_parameters(input_rows, input_cols);
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    Matrix_exception::is_values_null(values);
    start = new double [size];
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
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}


/*Matrix::Matrix(Matrix const &&matrix) noexcept {
    rows = matrix.rows;
    cols = matrix.cols;
    size = matrix.size;
    values = matrix.values;
    start = matrix.start;
}*/


unsigned int Matrix::get_rows(int print_flag) const {
    if (print_flag == 1)
        std::cout << "rows: " << rows;
    return rows;
}


unsigned int Matrix::get_cols(int print_flag) const {
    if (print_flag == 1)
        std::cout << "cols: " << cols;
    return cols;
}


unsigned int Matrix::get_size(int print_flag) const {
    if (print_flag == 1)
        std::cout << "size: " << size;
    return size;
}


Matrix Matrix::error() {
    Matrix error(0,0);
    return error;
}


void Matrix::output() const {
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
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}


Matrix Matrix::operator + (Matrix const matrix) const {
    Matrix_exception::are_sizes_equal(rows, cols, matrix.rows, matrix.cols);
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator + (double number) const {
    Matrix_exception::is_number_nan(number);
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + number;
    return sum_matrix;
}


Matrix Matrix::operator - (Matrix const matrix) const {
    Matrix_exception::are_sizes_equal(rows, cols, matrix.rows, matrix.cols);
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator * (Matrix const matrix) const {
    if (cols != matrix.rows) {
        return error();
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


Matrix Matrix::operator * (double number) const {
    Matrix_exception::is_number_nan(number);
    Matrix operated_matrix(rows, cols);
    for(int cell = 0; cell < size; cell++)
        operated_matrix.start[cell] = start[cell] * number;
    return operated_matrix;
}


Matrix Matrix::minor_init(int crossed_row, int crossed_col) const {
    if (crossed_row < 0 || crossed_col < 0) {
        return error();
    }
    Matrix minor(rows-1, cols-1);
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
    if(rows != cols) {
        return NAN;
    }
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
    if (matrix.rows != matrix.cols) {
        return error();
    }
    Matrix inverse_added_matrix(matrix.rows, matrix.cols);
    if(matrix.rows == 1) {
        inverse_added_matrix = matrix;
        return inverse_added_matrix;
    }
    for(int row = 0; row < matrix.rows; row++) {
        for(int col = 0; col < matrix.cols; col++) {
            Matrix minor = matrix.minor_init(row, col);
            int k = ((row + col) % 2 == 0) ? 1 : -1;
            inverse_added_matrix.values[row][col] = k * minor.determinant();
        }
    }
    return inverse_added_matrix;
}


Matrix Matrix::inversion() const {
    if (rows != cols || std::abs(this->determinant()) < EPSILON) {
        return error();
    }
    double determinant = this->determinant();
    double inv_det = 1 / determinant;
    Matrix transformed_matrix = minor_transformation(this->transposition());
    Matrix inverse_matrix = transformed_matrix * inv_det;
    return inverse_matrix;
}


Matrix Matrix::operator / (Matrix matrix) const {
    if (matrix.rows != matrix.cols || std::abs(matrix.determinant()) < EPSILON) {
        return error();
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


Matrix Matrix::operator / (double number) const {
    if (std::abs(number) < EPSILON) {
        return error();
    }
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


void calculation_check(double true_array[], Matrix matrix, std::string text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int cell = 0; cell < matrix.get_size(0); cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix.start[cell]) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[cell];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix.start[cell] << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


void test() {
    Matrix res_matrix(2, 2, 0.0);

    double array1[] = {2, 8, 1, 3};
    Matrix matrix1(2,2, array1);

    double array2[] = {4, 9, 21, 13};
    Matrix matrix2(2,2, array2);

    //  = overload test
    res_matrix = matrix1;
    double eq_true_array[] = {2, 8, 1, 3};
    calculation_check(eq_true_array, res_matrix, "= overload");

    //  addition test (matrix)
    res_matrix = matrix1 + matrix2;
    double sum_true_array[] = {6, 17, 22, 16};
    calculation_check(sum_true_array, res_matrix, "addition (matrix)");

    //  addition test (number)
    res_matrix = matrix1 + 2;
    double snum_true_array[] = {4, 10, 3, 5};
    calculation_check(snum_true_array, res_matrix, "addition (number)");

    //  subtraction test
    res_matrix = matrix1 - matrix2;
    double sub_true_array[] = {-2, -1, -20, -10};
    calculation_check(sub_true_array, res_matrix, "subtraction");

    //  multiplication test
    res_matrix = matrix1 * matrix2;
    double multi_true_array[] = {176, 122, 67, 48};
    calculation_check(multi_true_array, res_matrix, "multiplication (matrix)");

    //  multiplication test (number)
    res_matrix = matrix1 * 2;
    double mnum_true_array[] = {4, 16, 2, 6};
    calculation_check(mnum_true_array, res_matrix, "multiplication (number)");

    //  determinant test
    double determinant_true_array[] = {-2};

    double determinant = matrix1.determinant();
    Matrix det_matrix(1, 1, determinant);
    calculation_check(determinant_true_array, det_matrix, "determinant");

    //  transposition test
    double transp_true_array[] = {2, 1, 8, 3};
    res_matrix = matrix1.transposition();
    calculation_check(transp_true_array, res_matrix, "transposition");

    //  inversion test
    double inv_true_array[] = {-1.5, 4, 0.5, -1};
    res_matrix = matrix1.inversion();
    calculation_check(inv_true_array, res_matrix, "inversion");

    //  inverse multiplication test
    double inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
    res_matrix = matrix1 / matrix2;
    calculation_check(inv_multi_true_array, res_matrix, "inverse multiplication");

    //  power 0 test
    double pow0_true_array[] = {1, 0, 0, 1};
    res_matrix = matrix1.power(0);
    calculation_check(pow0_true_array, res_matrix, "power 0");

    //  power 3 test
    double pow3_true_array[] = {64, 216, 27, 91};
    res_matrix = matrix1.power(3);
    calculation_check(pow3_true_array, res_matrix, "power 3");

    //  power -4 test
    double pow4_true_array[] = {30.5625, -72.5, -9.0625, 21.5};
    res_matrix = matrix1.power(-4);
    calculation_check(pow4_true_array, res_matrix, "power -4");

    //  exp test
    double array3[] = {2, 2, 2, 2};
    Matrix matrix3(2, 2, array3);
    double exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
    res_matrix = Matrix::exp(matrix3);
    calculation_check(exp_true_array, res_matrix, "Matrix exp");
}


int main() {
    //test();
    //Matrix A(-1, 2);
    try {
        Matrix A(2, 2, 3);
        Matrix B(2, 2, 2);
        Matrix C = A + NAN;
        C.output();
    }
    catch(int ex_number) {
        std::cout << Matrix_exception::get_msg() << std::endl;
    }
    return 0;
}