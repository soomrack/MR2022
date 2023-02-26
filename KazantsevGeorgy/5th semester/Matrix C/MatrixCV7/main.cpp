#include "Matrix.h"
using namespace std;

Matrix::Matrix() {
    rows = 0;
    cols = 0;
    values = nullptr;
}

Matrix::Matrix(unsigned int m_rows, unsigned int m_cols) {
    rows = m_rows;
    cols = m_cols;
    values = new double[cols * rows];
}

Matrix::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new double[cols * rows];
    memcpy(values, other.values, rows * cols * sizeof(double)); //функция memcpe() копирует данные other.values в values
}

Matrix::~Matrix() {
    delete[] this->values;
}

Matrix Matrix::one_number(double n) {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = n;
    return *this;
}

Matrix Matrix::ite_rant() {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = i;
    return *this;
}

Matrix Matrix::rand_number(int min, int bar) {
    srand(time(nullptr));
    for(int i = 0; i < rows * cols; ++i)
        this->values[i] = double(rand() % bar + min);
    return *this;
}

void Matrix::m_output() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout  << values[i*cols + j] << " ";
        }
        cout << endl;
    }
}

Matrix Matrix::from_array(double* array) {
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}

Matrix Matrix::zero_matrix(unsigned int m_rows, unsigned int m_cols) {
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < m_rows * m_cols; ++i) {
        values[i] = 0.0;
    }
    return *this;
}

Matrix Matrix::single_matrix(unsigned int m_rows, unsigned int m_cols) {
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < rows ; i ++) {
        for (int j = 0; j < cols; j++) {
            if (i == j) {
                values[i * cols + j] = 1.0;
            } else
                values[i * cols + j] = 0.0;
        }
    }
    return *this;
}

bool Matrix::is_matrixequal(const Matrix& other) {
    return ((rows != other.rows) && (cols != other.cols));
}

bool Matrix::can_multiply(const Matrix& other) {
    return (rows == other.cols);
}

bool Matrix::can_determinant(const Matrix) { //в случае, если матрица квадратная возвращает 1, иначе 0.
    return(rows == cols);
}

Matrix Matrix::operator+(const Matrix &other) {
    Matrix Temp(this->rows, this->cols);
    if (is_matrixequal(other))
        return zero_matrix(this->rows, this->cols);
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] + other.values[i];
    return Temp;
}

Matrix Matrix::operator-(const Matrix &other) {
    Matrix Temp(this->rows, this->cols);
    if (is_matrixequal(other))
        return zero_matrix(this->rows, this->cols);
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] - other.values[i];
    return Temp;
}

Matrix Matrix::operator*(double num) {
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num * this->values[i];
    return Temp;
}



Matrix Matrix::operator*(const Matrix& other) {
    if (can_multiply(other) == false) return zero_matrix(rows, cols);
    cout << other.rows << endl << cols << endl;
    Matrix result(other.rows, cols);
    result.rows = other.rows;
    result.cols = cols;
    for(int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            double summa = 0.0;
            for (int k = 0; k < other.cols; k++) {
                summa += other.get(i, k) * get(k, j);
            }
            result.values[i * result.cols + j] = summa;
        }
    }
        return result;
}

Matrix Matrix::operator/(double num){
    Matrix Temp(this->rows, this->cols);
    for (int i = 0; i < rows * cols; i++) Temp.values[i] = num / this->values[i];
    return Temp;
}

Matrix& Matrix::operator=(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new double[cols * rows];
    for (int i = 0; i < rows*cols; ++i) {
        values[i] = other.values[i];
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, Matrix matrix)
{
    {
        for (unsigned int row = 0; row < matrix.rows; row++)
        {
            for (unsigned int col = 0; col < matrix.cols; col++)
            {
                out << matrix.values[row * matrix.cols + col] << "   ";
            }
            out << std::endl;
        }
        out << std::endl;
        return(out);
    }
}

double Matrix::get(int i, int j) const {
    return values[i * cols + j];
}

Matrix Matrix::transpose() {
    Matrix result(cols, rows);
    cout << result.rows << result.cols << endl;

        for (int i = 0; i < result.rows; ++i)
            for (int j = 0; j < result.cols; ++j) {
                result.values[i * result.cols + j] = values[j * result.rows + i];
            }
    return result;
}

Matrix Matrix::Minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
    Matrix temp(size - 1, size - 1);
    unsigned int shiftrow = 0;
    unsigned int shiftcol;
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        if (rows == row) {
            shiftrow = 1;
        }
        shiftcol = 0;
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) {shiftcol = 1;}
            temp.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow) * size + (cols + shiftcol)];
        }
    }
    return temp;
}

double Matrix::determinant(const Matrix matrix, unsigned int size)
{
    if (can_determinant(matrix) == 0) {
        std::cout << "Matrix not square";
        exit(0);
    };
    double det = 0;
    int k = 1;
    if (size == 0)
        return 0;
    if (size == 1)
        return matrix.values[0];
    if (size == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < size; idx++) {
        det += k * matrix.values[idx] * determinant(Minor(matrix, size, 0, idx), size - 1);
        k = -k;
    }
    return det;
}

int main() {
    Matrix A, B, C;
    double detA, detB;
    double data[4] = {1, 2,
                      3, 6};
    A = Matrix(2, 2);
    A = Matrix(2, 2).from_array(data);
    std::cout << A << '\n' << A.determinant(A, 2) << '\t';
    if (A.determinant(A, 2) == 0) cout << "det test passed"; else cout << "det test failed";
}