#include <iostream>
#include <cmath>


#define EPSILON 0.0001


class Matrix {
private:
    int rows;
    int cols;
public:
    int size;
    double **values;
    double *start;

    Matrix(int input_rows, int input_cols);
    ~Matrix();
    Matrix(Matrix const &matrix);
    void output() const;
    void filling(double number) const;
    int filling(double const array[]) const;
    //Matrix operator = (double i);
    Matrix &operator = (Matrix const &matrix);
    Matrix operator + (Matrix matrix) const;
    Matrix operator + (double number) const;
    Matrix operator - (Matrix matrix) const;
    Matrix operator * (Matrix matrix) const;
    Matrix minor_init(int crossed_row, int crossed_col) const;
    double determinant() const;
};


/*unsigned int len(double array[]) {
    printf("%lu\n", std::begin(array));
    printf("%lu\n", std::end(array));
}*/


Matrix::Matrix(int input_rows, int input_cols) {
    rows = input_rows;
    cols = input_cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double [size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
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
    start = new double[size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}


void Matrix::output() const {

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}


void Matrix::filling(double number) const {
    for (int cell = 0; cell < size; cell++)
        start[cell] = number;
}


int Matrix::filling(double const array[]) const {
    for (int cell = 0; cell < size; cell++)
        start[cell] = array[cell];
    return NAN;
}


/*Matrix Matrix::operator = (double i) {

}*/


Matrix &Matrix::operator = (Matrix const &matrix) {
    rows = matrix.rows;
    cols = matrix.cols;
    size = rows * cols;
    values = new double *[rows];
    start = new double[size];
    for (int row = 0; row < rows; row++)
        values[row] = start + row * cols;
    for (int cell = 0; cell < size; cell++)
        start[cell] = matrix.start[cell];
}


Matrix Matrix::operator + (Matrix const matrix) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator + (double number) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] + number;
    return sum_matrix;
}


Matrix Matrix::operator - (Matrix const matrix) const {
    Matrix sum_matrix(2,2);
    for (int cell = 0; cell < size; cell++)
        sum_matrix.start[cell] = start[cell] - matrix.start[cell];
    return sum_matrix;
}


Matrix Matrix::operator * (Matrix const matrix) const {
    Matrix multiplied_matrix(cols, matrix.rows);
    for(int row = 0; row < multiplied_matrix.rows; row++)
        for(int col = 0; col < multiplied_matrix.cols; col++) {
            multiplied_matrix.values[row][col] = 0;
            for (int k = 0; k < cols; k++)
                multiplied_matrix.values[row][col] += values[row][k] * matrix.values[k][col];
        }
    return multiplied_matrix;
}


Matrix Matrix::minor_init(int crossed_row, int crossed_col) const {
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


void calculation_check(double true_array[], Matrix matrix, std::string text) {
    int error_flag = 0;
    std::cout << text << " check:\n";
    for (int cell = 0; cell < matrix.size; cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix.start[cell]) > EPSILON || matrix.start[cell] == NAN) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << true_array[cell] << " res: " << matrix.start[cell] << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


void test() {
    Matrix res_matrix(2, 2);
    res_matrix.filling(NAN);

    Matrix matrix1(2,2);
    double array1[] = {2, 8, 1, 3};
    matrix1.filling(array1);

    Matrix matrix2(2,2);
    double array2[] = {4, 9, 21, 13};
    matrix2.filling(array2);

    //overload =
    res_matrix = matrix1;
    double eq_true_array[] = {2, 8, 1, 3};
    calculation_check(eq_true_array, res_matrix, "overload =");

    //addition check (matrix)
    res_matrix = matrix1 + matrix2;
    double sum_true_array[] = {6, 17, 22, 16};
    calculation_check(sum_true_array, res_matrix, "addition check (matrix)");

    //addition check (number)
    res_matrix = matrix1 + 2;
    double snum_true_array[] = {4, 10, 3, 5};
    calculation_check(snum_true_array, res_matrix, "addition check (number)");

    //subtraction check
    res_matrix = matrix1 - matrix2;
    double sub_true_array[] = {-2, -1, -20, -10};
    calculation_check(sub_true_array, res_matrix, "subtraction check");

    //multiplication check
    res_matrix = matrix1 * matrix2;
    double multi_true_array[] = {176, 122, 67, 48};
    calculation_check(multi_true_array, res_matrix, "multiplication check");

    //determinant check
    double determinant_true_array[] = {-2};
    Matrix det_matrix(1, 1);
    double determinant = matrix1.determinant();
    det_matrix.filling(determinant);
    calculation_check(determinant_true_array, det_matrix, "determinant check");

}


int main() {
    test();
    return 0;
}