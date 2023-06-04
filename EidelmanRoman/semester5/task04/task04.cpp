#include <iostream>
#include <cstring>
#include <cmath>



class MatrixException: public std::exception {
private:
    std::string message;
public:
    explicit MatrixException(std::string input_message);
    MatrixException(const MatrixException &X) = default;
    ~MatrixException() override = default;

    std::string getMessage() const;
};


MatrixException::MatrixException(std::string input_message) {
    message = std::move(input_message);
}


std::string MatrixException::getMessage() const {
    return message;
}



template <typename T>
class Matrix {
private:
    unsigned int rows = 0;
    unsigned int cols = 0;
    unsigned int matrix_size = rows * cols;
    T** values = nullptr;
    T* data = nullptr;

public:
    Matrix() = default;
    Matrix(unsigned int input_rows, unsigned int input_cols);
    Matrix(const Matrix<T>& X);
    Matrix(Matrix&& X) noexcept;
    Matrix(unsigned int input_rows, unsigned int input_cols, T x);
    ~Matrix();

    Matrix<T>& operator=(const Matrix& X);
    Matrix<T>& operator=(Matrix&& X) noexcept;
    Matrix<T>& operator+=(const Matrix& X);
    Matrix<T> operator+(const Matrix& X);
    Matrix<T>& operator-=(const Matrix& X);
    Matrix<T> operator-(const Matrix& X);
    Matrix<T>& operator*=(const Matrix& X);
    Matrix<T> operator*(const Matrix& X);
    Matrix<T> operator^(unsigned int b);
    Matrix<T> operator/(T b);

    void print();
};



template <typename T>
Matrix<T>::Matrix(unsigned int input_rows, unsigned int input_cols) {
    rows = input_rows;
    cols = input_cols;
    matrix_size = rows * cols;
    data = new T [matrix_size];
    values = new T *[rows];
    if (data == nullptr || values == nullptr) {
        delete[] data;
        delete[] values;
        throw MatrixException("Memory error!\n");
    }
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}


template <typename T>
Matrix<T>::Matrix(const Matrix& X) {
    if (this != &X) {
        rows = X.rows;
        cols = X.cols;
        matrix_size = X.matrix_size;
        data = new T [matrix_size];
        values = new T *[rows];
        memcpy(data, X.data,  matrix_size * sizeof(T));
        for (int row = 0; row < rows; ++row)
            values[row] = data + row * cols;
    }
}


template <typename T>
Matrix<T>::Matrix(Matrix&& X) noexcept {
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = X.data;
    values = X.values;
    X.data = nullptr;
    X.values = nullptr;
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
}


template <typename T>
Matrix<T>::Matrix(unsigned int input_rows, unsigned int input_cols, T x): Matrix(input_rows, input_cols) {
    for (int i = 0; i < matrix_size; ++i) {
        data[i] = x;
    }
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] data;
    delete[] values;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& X) {
    if (this == &X) {
        return *this;
    }
    delete[] data;
    delete[] values;
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = new T [matrix_size];
    values = new T *[rows];
    memcpy(data, X.data,  matrix_size * sizeof(T));
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& X) noexcept {
    if (this == &X) {
        return *this;
    }
    delete[] data;
    delete[] values;
    rows = X.rows;
    cols = X.cols;
    matrix_size = X.matrix_size;
    data = X.data;
    values = X.values;
    X.data = nullptr;
    X.values = nullptr;
    for (int row = 0; row < rows; ++row)
        values[row] = data + row * cols;
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& X) {
    if (rows != X.rows || cols != X.cols) {
        throw MatrixException("Sizes don't match!\n");
    }
    for (int i = 0; i < matrix_size; ++i)
        data[i] += X.data[i];
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& X) {
    Matrix<T> copy = *this;
    copy += X;
    return copy;
}

template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& X) {
    if (rows != X.rows || cols != X.cols) {
        throw MatrixException("Sizes don't match!\n");
    }
    for (int i = 0; i < matrix_size; ++i)
        data[i] -= X.data[i];
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T>& X) {
    Matrix<T> copy = *this;
    copy -= X;
    return copy;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& X) {
    if (cols != X.rows) {
        throw MatrixException("Wrong size for multiplication!\n");
    }
    Matrix<T> zero(rows, cols, 0);
    for (int row = 0; row < zero.rows; ++row) {
        for (int col = 0; col < zero.cols; ++col) {
            for (int k = 0; k < zero.rows; ++k) {
                zero.values[row][col] += values[row][k] * X.values[k][col];
            }
        }
    }
    *this = zero;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& X) {
    Matrix<T> copy = *this;
    copy *= X;
    return copy;
}

template <typename T>
Matrix<T> Matrix<T>::operator^(unsigned int b) {
    Matrix<T> copy = *this;
    for (int i = 1; i < b; ++i)
        *this = *this * copy;
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::operator/(T b) {
    if (b == 0)
        throw MatrixException("Division by zero!\n");
    for (int i = 0; i < matrix_size; ++i)
        data[i] /= b;
    return *this;
}

template <typename T>
void Matrix<T>::print() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++)
            std::cout << values[row][col] << "  ";
        std::cout << "\n";
    }
    std::cout << "\n";
}



template<typename T>
class EMatrix: public Matrix<T> {
private:
    static inline unsigned int k = 0; // static
    static inline unsigned int final_size = 0;
    static unsigned int calcMemory(unsigned int c_rows, unsigned int c_cols);
private:
    unsigned int mem_size{};
public:
    EMatrix();
    EMatrix(unsigned int input_rows, unsigned int input_cols);
    EMatrix(const EMatrix<T>& X);
    EMatrix(EMatrix<T>&& X) noexcept;
    EMatrix(unsigned int input_rows, unsigned int input_cols, T x);
    ~EMatrix();

    EMatrix<T>& operator=(const EMatrix& X);
    EMatrix<T>& operator=(EMatrix<T>&& X) noexcept;

    unsigned int get_k();
    unsigned int get_final_size();
    unsigned int get_mem_size();
};



template<typename T>
unsigned int EMatrix<T>::calcMemory(unsigned int c_rows, unsigned int c_cols) {
    return c_rows * c_cols * sizeof(T) + c_rows * sizeof(T *);
}


template<typename T>
EMatrix<T>::EMatrix(): Matrix<T>() {
    k++;
    mem_size = 0;
}


template<typename T>
EMatrix<T>::EMatrix(unsigned int input_rows, unsigned int input_cols): Matrix<T>(input_rows, input_cols) {
    k++;
    mem_size = calcMemory(input_rows, input_cols);
    final_size += mem_size;
}


template<typename T>
EMatrix<T>::EMatrix(const EMatrix<T> &X): Matrix<T>(X) {
    k++;
    mem_size = X.mem_size;
    final_size += mem_size;
}


template<typename T>
EMatrix<T>::EMatrix(EMatrix<T>&& X) noexcept: Matrix<T>(X) {
    k++;
    mem_size = X.mem_size;
    X.mem_size = 0;
}

template<typename T>
EMatrix<T>::EMatrix(unsigned int input_rows, unsigned int input_cols, T x): Matrix<T>(input_rows, input_cols, x) {
    k++;
    mem_size = calcMemory(input_rows, input_cols);
    final_size += mem_size;
}


template<typename T>
EMatrix<T>::~EMatrix() {
    k--;
    final_size -= mem_size;
    mem_size = 0;
}


template<typename T>
EMatrix<T>& EMatrix<T>::operator=(const EMatrix<T> &X) {
    Matrix<T>::operator=(X);
    final_size += X.mem_size - mem_size;
    mem_size = X.mem_size;
    return *this;
}


template<typename T>
EMatrix<T>& EMatrix<T>::operator=(EMatrix<T>&& X) noexcept {
    Matrix<T>::operator=(X);
    final_size += X.mem_size - mem_size;
    mem_size = X.memory_size;
    X.mem_size = 0;
    return *this;
}


template<typename T>
unsigned int EMatrix<T>::get_k() {
    return k;
}


template<typename T>
unsigned int EMatrix<T>::get_final_size() {
    return final_size;
}


template<typename T>
unsigned int EMatrix<T>::get_mem_size() {
    return mem_size;
}


int main() {
    short n = 2;
    short m = 2;
    EMatrix<double> B;
    EMatrix<double> A(n, m, 3);

    B = A;


    try {
        B / 0;
    }
    catch(MatrixException &Exception_object) {
        std::cout << Exception_object.getMessage();
    }

    std::cout << B.get_final_size() << "\n";
    std::cout << B.get_k() << "\n";

    return 0;
}