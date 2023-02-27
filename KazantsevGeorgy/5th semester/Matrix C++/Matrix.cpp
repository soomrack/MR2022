#include "Matrix.h"
#include <fstream>
#include <exception>
using namespace std;
const double EPS = 0.000005;

//  Исключения
Matrix_Exception EQUAL("Matrix not equal)\n");
Matrix_Exception NOTSQUARE("Matrix not square!\n");
Matrix_Exception MEMORY_ERROR("Memory error\n");
Matrix_Exception SIZE_ERROR("mismatch of matrix sizes");

//Перегрузка оператора вывода
template <typename R>
std::ostream& operator<<(std::ostream& out, Matrix<R> matrix)
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

// Конструктор создания пустой матрицы размером 0 на 0
template <typename T>
Matrix<T>::Matrix() {
    rows = 0;
    cols = 0;
    values = nullptr;
}

// Конструктор создает матрицу размером m_rows и m_cols
template <typename T>
Matrix<T>::Matrix(unsigned int m_rows, unsigned int m_cols) {
    rows = m_rows;
    cols = m_cols;
    values = new T[cols * rows];
    if (values == nullptr) throw MEMORY_ERROR;
}


template <typename T>
Matrix<T>::Matrix(Matrix&& matrix) noexcept : values(matrix.values), rows(matrix.rows), cols(matrix.cols)
{
    matrix.values = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

// Конструктор копирания значений другой матрицы
template <typename T>
Matrix<T>::Matrix(const Matrix& other) {
    rows = other.rows;
    cols = other.cols;
    values = new T[cols * rows];
    if (values==nullptr) throw MEMORY_ERROR;
    memcpy(values, other.values, rows * cols * sizeof(T)); //функция memcpe() копирует данные other.values в values
}

// освобождает память, выделенную под матрицу
template <typename T>
Matrix<T>::~Matrix() {
    delete[] this->values;
}

// метод заполняет всю матрицу одним числом n
template <typename T>
Matrix<T> Matrix<T>::one_number(T n) {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = n;
    return *this;
}

// метод заполняет матрицу нулем и натуральными числами
template <typename T>
Matrix<T> Matrix<T>::i_number() {
    for(int i = 0; i < rows * cols; ++i)
        values[i] = i;
    return *this;
}

//метод заполняет матрицу рандомным числом в диапозоне числа(минимальное значение = min, максимальное значение = max - 1)
template <typename T>
Matrix<T> Matrix<T>::rand_number(int min, int bar) {
    srand(time(nullptr));
    for(int i = 0; i < rows * cols; ++i)
        this->values[i] = T(rand() % bar + min);
    return *this;
}

// метод вывода матрицы
template <typename T>
void Matrix<T>::output() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout  << values[i*cols + j] << " ";
        }
        cout << endl;
    }
}

//метод заполняет матрицу нулевой матрицей
template <typename T>
Matrix<T> Matrix<T>::zero(unsigned int m_rows, unsigned int m_cols) {
    delete[] values;
    cols = m_cols;
    rows = m_rows;
    values = new double[cols * rows];
    for (int i = 0; i < m_rows * m_cols; ++i) {
        values[i] = 0.0;
    }
    return *this;
}

// метод заполняет матрицу значениями с массива
template <typename T>
Matrix<T> Matrix<T>::from_array(T* array) {
    memcpy(values, array, rows * cols * sizeof(T));
    return *this;
}

template <typename T>
void Matrix<T>::fill_certain(const unsigned int length, const T *array) {
    if (length != rows * cols) throw SIZE_ERROR;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        values[idx] = array[idx];
    }
}

//метод заполняет матрицу единичной матрицей
template <typename T>
Matrix<T> Matrix<T>::single(unsigned int m_rows, unsigned int m_cols) {
    cols = m_cols;
    rows = m_rows;
    values = new T[cols * rows];
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

// метод возвращает значение матрицы с позиции (i, j)
template <typename T>
T Matrix<T>::get(int i, int j) const {
    return values[i * cols + j];
}
template <typename T>
bool Matrix<T>::is_equal(const Matrix& other) {
    return ((rows != other.rows) && (cols != other.cols));
}
template <typename T>
bool Matrix<T>::is_multiply(const Matrix& other) {
    return (rows == other.cols);
}

// метод транспонирует матрицу
template <typename T>
void Matrix<T>::transpose(){
    unsigned int row = cols;
    unsigned int col = rows;
    T* temp = new T[rows * col];

    for (unsigned int row_idx = 0; row_idx < rows; row_idx++){
        for (unsigned int col_idx = 0; col_idx < cols; col_idx++){
            temp[col_idx * rows + row_idx] = values[row_idx * cols + col_idx];
        }
    }

    delete[] values;
    values = temp;
    rows = row;
    cols = col;
}


template <typename T>
Matrix<T> Matrix<T>::Minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col) {
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

template <typename T>
double Matrix<T>::determinant(const Matrix matrix, unsigned int size)
{
    if (matrix.cols != matrix.rows) throw NOTSQUARE;
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

template <typename T>
void Matrix<T>::exponent(const unsigned int degree) {
    if (rows != cols) throw NOTSQUARE;

    Matrix<T> rezult = Matrix<T>(rows, cols);
    rezult.single(rows, cols);
    T rate = 1;
    Matrix<T> temp = rezult;
    for (unsigned int idx = 1; idx < degree; idx++){
        temp = temp * *this;
        rate /= (idx);
        rezult = rezult + (temp * rate);
    }

    *this = rezult;
}

template <typename T>
void Matrix<T>::pow(const unsigned int n) {
    if (rows != cols) throw NOTSQUARE;

    Matrix<T> rezult = Matrix<T>(rows, cols);
    rezult.single(rows, cols);
    for (unsigned int idx = 0; idx < n; idx++) {
        rezult = rezult * *this;
    }

    this->fill_certain(rows * cols, rezult.values);
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> matrix)
{
    if (this->cols != matrix.cols || this->rows != matrix.rows) return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
        if (abs(this->values[idx] - matrix.values[idx]) > EPS) return false;
    }
    return true;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& matrix) noexcept
{
    if (this == &matrix) return *this;
    delete[] matrix.values;
    rows = matrix.rows;
    cols = matrix.cols;
    values = matrix.values;
    matrix.values = nullptr;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &other) {
    Matrix Temp(other.rows, other.cols);
    if (is_equal(other)) throw EQUAL;
    for (int i = 0; i < rows * cols; ++i) Temp.values[i] = this->values[i] + other.values[i];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &other) {
    Matrix Temp(this->rows, this->cols);
    if (is_equal(other)) throw EQUAL;
    for (int idx = 0; idx < rows * cols; idx++) Temp.values[idx] = this->values[idx] - other.values[idx];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(T num) {
    Matrix Temp(this->rows, this->cols);
    for (int idx = 0; idx < rows * cols; idx++) Temp.values[idx] = num * this->values[idx];
    return Temp;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) {
    if (is_multiply(other) == false) throw EQUAL;
    Matrix result(other.rows, cols);
    result.rows = other.rows;
    result.cols = cols;
    for(int idx = 0; idx < result.rows; idx++) {
        for (int jdx = 0; jdx < result.cols; jdx++) {
            double summa = 0.0;
            for (int k = 0; k < other.cols; k++) {
                summa += other.get(idx, k) * get(k, jdx);
            }
            result.values[idx * result.cols + jdx] = summa;
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T num){
    Matrix Temp(this->rows, this->cols);
    for (int idx = 0; idx < rows * cols; idx++) Temp.values[idx] = num / this->values[idx];
    return Temp;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    rows = other.rows;
    cols = other.cols;
    values = new T[cols * rows];
    if (values == nullptr) throw MEMORY_ERROR;
    for (int idx = 0; idx < rows*cols; ++idx) {
        values[idx] = other.values[idx];
    }
    return *this;
}

void test_det() {
    Matrix<double> A;
    double data_det[16] = {1.0, 5.0, 5.0, 2.0,
                      2.0, 5.0, -2.0, 2.0,
                       7.0, 0.0, 2.0, 5.0,
                      3.0, 1.0, 5.0, 1.0};
    A = Matrix<double>(4, 4).from_array(data_det);
    if (A.determinant(A, 4) == 437) cout << "det test passed\n"; else cout << "det test failed\n";
}

void test_transpose() {
    Matrix<double> A, B;
    double data_transpose[9] = {1.0 , 2.0, 3.0 ,
                                4.0, 5.0, 6.0,
                                7.0, 8.0, 9.0};

    double data_transpose_[9] = {1.0 , 4.0, 7.0 ,
                                2.0, 5.0, 8.0,
                                3.0, 6.0, 9.0};
    A = Matrix<double>(3,3).from_array(data_transpose);
    B = Matrix<double>(3,3).from_array(data_transpose_);
    B.transpose();
    bool flag = A == B;
    if (flag == 1) cout << "Transpose test passed!\n"; else cout << "Transpose test failed\n";
}

void test_power() {
    Matrix<float> A, B;
    float data_power[9] = {1.0 , 2.0, 3.0 ,
                                3.0, 3.0, 3.0,
                                3.0, 3.0, 3.0};
    float data_power_[9] = {16.0 , 17.0, 18.0 ,
                            21.0, 24.0, 27.0,
                            21.0, 24.0, 27.0};
    A = Matrix<float>(3,3).from_array(data_power);
    B = Matrix<float>(3,3).from_array(data_power_);
    bool flag;
    A.pow(3);
    flag = B == A;
    if (flag == 1) cout << "Power test passed!\n"; else cout << "power test failed\n";
}

void exception_module(){
    Matrix<double> A;
    A = Matrix<double>(3,2).single(3, 2);
    double det;
    try {
        cout << A;
    }
    catch(const Matrix_Exception& e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    try {
        det = A.determinant(A, 3);
        cout << det;
    }
    catch(const Matrix_Exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }

    try {
        double data_array_copy[9] = {1.0 , 2.0, 3.0 ,
                                     3.0, 3.0, 3.0,
                                     3.0, 3.0, 3.0};
        Matrix<double> A;
        A = Matrix<double>(3,3);
        A.fill_certain(9, data_array_copy);
    }
    catch(const Matrix_Exception e)
    {
        std::cerr << "Caught: " << e.what() << std::endl;
        std::cerr << "Type: " << typeid(e).name() << std::endl;
    }
}



// блок подсчета памяти
template <typename T>
class Matrix_memory : public Matrix<T> { // наследование с основного классаа Matrix<T>
protected:
    unsigned int memory_size;
    static unsigned int count; // кол-во matrix_memory
    static unsigned int total_memory;
public:
    Matrix_memory(){
        this->rows = 0;
        this->cols = 0;
        this->values = nullptr;
        memory_size = 0;

        count++;
        memory += memory_size;
        total_memory += memory_size;
    }

    Matrix_memory(const unsigned int n){
        this->rows = n;
        this->cols = n;
        this->values = new T [n * n];
        memory_size = n * n * sizeof (T);

        count++;
        memory += memory_size;
        total_memory += memory_size;
    }

    Matrix_memory(const unsigned int row, unsigned int col){
        this->rows = row;
        this->cols = col;
        this->values = new T [row * col];
        memory_size = row * col * sizeof (T);

        count++;
        memory += memory_size;
        total_memory += memory_size;
    }

    //деструктор
    ~Matrix_memory() {
        count--;
        memory -= memory_size;
        total_memory -= memory_size;
    };

    Matrix_memory<T> operator=(const Matrix_memory<T> &matrix);
    static int getQuantity() { return count; };
    static int getMemory() { return total_memory; };
    void output();
};
template <typename T>
unsigned int Matrix_memory<T>::total_memory = 0;
template <typename T>
unsigned int Matrix_memory<T>::count = 0;

template <typename T>
Matrix_memory<T> Matrix_memory<T>::operator=(const Matrix_memory<T> &matrix) {
    if (this != &matrix) {
        if (!this->values)
            delete[] this->values;

        memory -= memory_size;
        total_memory -= memory_size;

        this->rows = matrix.rows;
        this->cols = matrix.cols;
        memory_size = this->rows * this->cols * sizeof(T);

        this->values = new T[matrix.rows * matrix.cols];
        for (unsigned int idx = 0; idx < this->rows * this->cols; idx++) {
            this->values[idx] = matrix.values[idx];
        }

        memory += memory_size;
        total_memory += memory_size;
    }
}

template <typename T>
void Matrix_memory<T>::output() {
        std::cout << "Temp memory " << memory_size << "bytes\n";
        std::cout << "Count: " << getQuantity() << "\n";
        std::cout << "Part of general " << getMemory() << "/" << memory << " bytes\n\n\n";
}

void test_memory_module() {
    Matrix_memory<double> first = Matrix_memory<double>(3, 5);
    first.output();
    Matrix_memory<float> second= Matrix_memory<float>(3, 5);
    second.output();
};

int main() {
    test_memory_module();
    exception_module();
    test_power();
    test_transpose();
    test_det();
}
