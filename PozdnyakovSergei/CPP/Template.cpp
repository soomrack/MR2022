#include <iostream>
#include <cstdlib>
/*
#include <cmath>
*/
#include <cstring>

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NOTSQUAREMATRIX("Matrix must be square\n");
Matrix_Exception ERRORSIZE("Matrix have not equal size\n");


template<typename T>
class Matrix {
protected:
    unsigned int cols;
    unsigned int rows;
    T *value;

public:
    Matrix();
    Matrix(unsigned int col, unsigned int row);
    Matrix(unsigned int col);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    ~Matrix();


    virtual void print();
    void set_random(const unsigned int);
    void set_values(const unsigned int l, const T* array);

    Matrix<T> operator+(const Matrix<T>&);
    Matrix<T> operator-(const Matrix<T>&);
    Matrix<T> operator*(const Matrix<T>&);
    Matrix<T> operator*(const T);
    Matrix<T> operator/(const T) const;
    Matrix<T> exponent(const Matrix<T>&, const unsigned int);
    Matrix<T> minor(Matrix<T>&, const unsigned int row, const unsigned int col);
    Matrix<T> transpose();
    double determinant(const Matrix<T>&);
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T>& operator=(Matrix<T>&&) noexcept ;
    Matrix<T> power (const Matrix<T>&, const unsigned int);

    friend std::ostream& operator<<(std::ostream& out, Matrix<T> matrix)
    {
        {
            for(unsigned int row = 0; row < matrix.rows; row++)
            {
                for(unsigned int col = 0; col <matrix.cols; col++)
                {
                    out << matrix.value[row*matrix.cols +col] << "\t";
                }
                out << std::endl;
            }
            out << std::endl;
            return out;
        }
    }
};


template <typename T>
Matrix<T>::Matrix() {
    cols = 0;
    rows = 0;
    value = nullptr;
}

template <typename T>
Matrix<T>:: ~Matrix()
{
    if (value != nullptr)
        delete [] value;
}

template <typename T>
Matrix<T>::Matrix(unsigned int col, unsigned int row) {
    cols = col;
    rows = row;
    unsigned int n_values = cols * rows;
    value = new T[cols*rows];
    for (unsigned int idx = 0; idx < n_values; ++idx) {
        value[idx] = 0.0;
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    value = new T[rows * cols];
    memcpy(value,matrix.value,rows * cols * sizeof(T));
}


template <typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) noexcept {
    cols = matrix.cols;
    rows = matrix.rows;
    value = matrix.value;
    matrix.value = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

template <typename T>
void Matrix<T>::print() {
    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
            std::cout << value[row * cols + col] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

template <typename T>
void Matrix<T>::set_random(const unsigned int n) {
    for (unsigned int index = 0; index < rows * cols; ++index) {
        value[index] = rand() % n;
    }
}


template <typename T>
void Matrix<T>::set_values(const unsigned int l, const T *array) {
    for (unsigned int number = 0; number < rows * cols; number++) {
        value[number] = array[number];
    }
}


template <typename T>
Matrix<T>::Matrix(unsigned int col) {
    cols = col;
    rows = col;
    value = new T[cols * rows];
    for (unsigned int row = 0; row < rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            value[row * cols + col] = (row == col) ? 1 : 0;

        }
    }
}


template <typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& matrix) {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix itog(matrix);
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number++) {
        itog.value[number] += value[number];
    }
    return itog;
}


template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix itog(matrix);
    for (unsigned int number = 0; number < matrix.cols * matrix.rows; number++) {
        itog.value[number] -= value[number];
    }
    return itog;
}


template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix itog(matrix);
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row* itog.rows + col] = 0.00;
            for (unsigned int k = 0; k < itog.cols; k++) {
                itog.value[row * itog.cols + col] += value[row * cols + k] * matrix.value[k * itog.cols + col];
            }
        }
    }
    return itog;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T num) {
    Matrix itog(cols, rows);
    for (unsigned int number = 0; number< rows * cols; number++) {
        itog.value[number] = value[number] * num;
    }
    return itog;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& matrix)  {
    if (this == &matrix) return *this;
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]value;
    value = new T[cols * rows];
    memcpy(value, matrix.value, rows * cols * sizeof(T));
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& matrix) noexcept {
    if (this == &matrix) return *this;
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]value;
    value = matrix.value;
/*
    memcpy(value, matrix.value, rows * cols * sizeof(T));
*/
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator/(const T num) const {
    Matrix itog(cols, rows);
    for(unsigned int number = 0; number < rows * cols; ++number) {
        itog.value[number] = value[number]/num;
    }
    return itog;
}


template <typename T>
Matrix<T> Matrix<T>::exponent(const Matrix<T>& M, const unsigned int acc){
    if (M.rows != M.cols) throw NOTSQUAREMATRIX;
    Matrix itog(M.cols);
    Matrix temp(M.cols);
    double factorial = 1.0;
    for (int number = 1; number < acc; number++) {
        factorial *= number;
        temp = temp * M;
        itog = itog + temp / factorial;
    }
    return itog;
}


template <typename T>
Matrix<T> Matrix<T>::power (const Matrix<T>& M, const unsigned int n) {
    if (M.rows != M.cols) throw NOTSQUAREMATRIX;
    Matrix<T> itog (rows, cols);
    itog.unit_matrix();
    for (unsigned int number = 1; number <= n; number++) {
        itog *= *this;
    }
    *this = itog;
}


template <typename T>
Matrix<T> Matrix<T>::minor(Matrix<T>& M, unsigned int row, unsigned int col) {
    int new_row = M.rows -1;
    int new_col = M.cols - 1;
    if (row >= M.rows) new_row++;
    if (col >= M.cols) new_col++;

    Matrix itog = Matrix(new_row, new_col);
    unsigned int k = 0;

    for (unsigned int number = 0; number < rows * cols; number++){
        if ((number % cols == col) or (number / cols == row)) continue;
        itog.values[k++] = M.values[number];
    }

    return itog;
}


template <typename T>
Matrix<T> Matrix<T>::transpose() {
    Matrix itog = {cols, rows};
    for (unsigned int row = 0; row < itog.rows; row++) {
        for (unsigned int col = 0; col < itog.cols; col++) {
            itog.value[row * itog.cols + col] = value[col * itog.cols + row];
        }
    }
    return itog;
}


template <typename T>
double Matrix<T>::determinant(const Matrix<T>& matrix) {
    if(cols != rows) throw NOTSQUAREMATRIX;
    double det = 0;
    int sign = 1;
    if (rows == 0 and cols == 0)
        return 0;
    if (rows == 1 and cols == 1)
        return matrix.values[0];
    if (rows == 2 and cols == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int number = 0; number < rows; number++) {
        det += sign * matrix.values[number] * determinant(Minor(matrix, 0, number), rows - 1);
        sign = -sign;
    }
    return det;
}

template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
    static unsigned long int memory_size;
    static unsigned long int total_memory;
    static unsigned long int quantity;
public:
    Matrix_Memory<T1>();
    Matrix_Memory<T1>(unsigned int, unsigned int);
    Matrix_Memory<T1>(const Matrix_Memory<T1>&);
    Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
    ~Matrix_Memory();
    Matrix_Memory<T1>&  operator= (const  Matrix_Memory<T1>& );
    Matrix_Memory<T1>&  operator= (Matrix_Memory<T1>&& ) noexcept ;
    virtual void print();
};

template <typename T>
Matrix_Memory<T>&::Matrix_Memory<T>::operator=(const Matrix_Memory<T> &matrix) {
    if (this == &matrix) return *this;

    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[] this->values;
    this->values = new T[this->cols * this->rows];
    memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));
    memory_size += matrix.memory_size;
    total_memory += memory_size;
    quantity++;
    return *this;
}

template <typename T>
Matrix_Memory<T>& Matrix_Memory<T>::operator= (Matrix_Memory<T>&& matrix) noexcept {
    if (this == &matrix) return *this;
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[]this->value;
    this->value = matrix.value;
    //value = new T[cols * rows];
    //memcpy(value, matrix.value, rows * cols * sizeof(T));
    memory_size += matrix.memory_size;
    total_memory += memory_size;
    quantity++;
    return *this;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col) /*: Matrix<T>(row, col)*/ {
    this->rows = row;
    this->cols = col;
    this->value = new T[this->rows * this->cols];
    memory_size = row * col * sizeof(T);
    total_memory += memory_size;
    quantity++;
}


template <typename T>
Matrix_Memory<T>::~Matrix_Memory() {
    total_memory -= memory_size;
    quantity--;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& m)/* : Matrix<T>(m)*/ {
    this->values = new T[this->rows * this->cols];
    memcpy(this->value, m.value, sizeof(T) * this->rows * this->cols);
    memory_size = m.memory_size;
    total_memory += memory_size;
    quantity++;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& m) noexcept {
memory_size = m.memory_size;

m.rows = 0;
m.cols = 0;
m.values = nullptr;
m.memory_size = 0;
}


template <typename T>
void Matrix_Memory<T>::print() {
    std::cout << "Used " << this->total_memory << " bytes" << std::endl;
    std::cout << "Made " << this->quantity << "matrices" << std::endl;
}

template <typename T>
unsigned long int Matrix_Memory<T>::total_memory = 0;
template <typename T>
unsigned long int Matrix_Memory<T>::memory_size = 0;

int main() {
    Matrix_Memory<double> m1(3,3);
    m1.set_random(10);
    std:: cout << m1;
    Matrix_Memory<double> m2(3, 3);
    m2.set_random(10);
    std:: cout << m2;
    std::cout << m1 + m2;
    std::cout << m1 - m2;
    std::cout << m1 * m2;
    std::cout << m1 * 3;
    std::cout << m1 / 3;
    std::cout << m1.exponent(m1,5);
    m1.print();
    return 0;
}