#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};


Matrix_Exception NOTSQUARE("Make matrix square\n");
Matrix_Exception ERRORSIZE("Change matrix size\n");


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
    Matrix(Matrix&& matrix);
    ~Matrix();


    void info();
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
Matrix<T>::Matrix(Matrix<T>&& matrix) {
    cols = matrix.cols;
    rows = matrix.rows;
    value = matrix.value;
    matrix.value = nullptr;
    matrix.rows = 0;
    matrix.cols = 0;
}

template <typename T>
void Matrix<T>::info() {
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
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.value[idx] += value[idx];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix result(matrix);
    for (unsigned int idx = 0; idx < matrix.cols * matrix.rows; idx++) {
        result.value[idx] -= value[idx];
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& matrix)  {
    if (rows != matrix.rows) throw ERRORSIZE;
    Matrix result(matrix);
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.value[row* result.rows + col] = 0.00;
            for (unsigned int k = 0; k < result.cols; k++) {
                result.value[row * result.cols + col] += value[row * cols + k] * matrix.value[k * result.cols + col];
            }
        }
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator* (const T num) {
    Matrix result(cols, rows);
    for (unsigned int number = 0; number< rows * cols; number++) {
        result.value[number] = value[number] * num;
    }
    return result;
}


template <typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& matrix)  {
    if (this == &matrix) {
        return *this;
    }
    rows = matrix.rows;
    cols = matrix.cols;
    delete[]value;
    value = new T[cols * rows];
    memcpy(value, matrix.value, rows * cols * sizeof(T));
    return *this;
}



template <typename T>
Matrix<T> Matrix<T>::operator/(const T num) const {
    Matrix result(cols, rows);
    for(unsigned int number = 0; number < rows * cols; ++number) {
        result.value[number] = value[number]/num;
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::exponent(const Matrix<T>& M, const unsigned int acc){
    if (M.rows != M.cols) throw NOTSQUARE;
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
    Matrix result = {cols, rows};
    for (unsigned int row = 0; row < result.rows; row++) {
        for (unsigned int col = 0; col < result.cols; col++) {
            result.values[row * result.cols + col] = value[col * result.cols + row];
        }
    }
    return result;
}

template <typename T>
double Matrix<T>::determinant(const Matrix<T>& matrix)
{
    if(cols != rows) throw NOTSQUARE;
    double det = 0;
    int sign = 1;
    if (rows == 0 and cols == 0)
        return 0;
    if (rows == 1 and cols == 1)
        return matrix.values[0];
    if (rows == 2 and cols == 2) {
        return (matrix.values[0] * matrix.values[3] - matrix.values[2] * matrix.values[1]);
    }
    for (unsigned int idx = 0; idx < rows; idx++) {
        det += sign * matrix.values[idx] * determinant(Minor(matrix, 0, idx), rows - 1);
        sign = -sign;
    }
    return det;
}

template <typename T1>
class Matrix_Memory : public Matrix<T1> {
private:
    static unsigned long memory_size;
    static unsigned long total_memory;
public:
    Matrix_Memory<T1>();
    Matrix_Memory<T1>(unsigned int, unsigned int);
    Matrix_Memory<T1>(const Matrix_Memory<T1>&);
    Matrix_Memory<T1>(Matrix_Memory<T1>&&) noexcept;
    ~Matrix_Memory();
    Matrix_Memory<T1>&  operator= (const  Matrix_Memory<T1>& );
    void info();
};

template <typename T>
Matrix_Memory<T>&::Matrix_Memory<T>::operator=(const Matrix_Memory<T> &matrix) {
    if (this == &matrix)
    {
        return *this;
    }
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    delete[] this->values;
    this->values = new T[this->cols * this->rows];
    memcpy(this->values, matrix.values, this->rows * this->cols * sizeof(T));
    memory_size += matrix.memory_size;
    total_memory += memory_size;
    return *this;
}

template <typename T>
Matrix_Memory<T>::Matrix_Memory()
{
    this->memory_size += 0;
    this->total_memory += 0;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(unsigned int row, unsigned int col)
{
    this->rows = row;
    this->cols = col;
    this->value = new T[this->rows * this->cols];
    memory_size = row * col * sizeof(T);
    total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::~Matrix_Memory()
{
    total_memory -= memory_size;
}
template <typename T>
Matrix_Memory<T>::Matrix_Memory(const Matrix_Memory<T>& matrix)
{
    this->values = new T[this->rows * this->cols];
    memcpy(this->values, matrix.values, sizeof(T) * this->rows * this->cols);
    memory_size = matrix.memory_size;
    total_memory += memory_size;
}


template <typename T>
Matrix_Memory<T>::Matrix_Memory(Matrix_Memory<T>&& matrix) noexcept
{

memory_size = matrix.memory_size;

matrix.rows = 0;
matrix.cols = 0;
matrix.values = nullptr;
matrix.memory_size = 0;
}


template <typename T>
void Matrix_Memory<T>::info()
{
    std::cout << "Total memory " << this->total_memory << " byte" << std::endl;
}

template <typename T>
unsigned long int Matrix_Memory<T>::total_memory = 0;
template <typename T>
unsigned long int Matrix_Memory<T>::memory_size = 0;

int main() {
    Matrix_Memory<float> m1(3,3);
    m1.set_random(10);
    std:: cout << m1;
    Matrix_Memory<float> m2(3, 3);
    m2.set_random(10);
    std:: cout << m2;
    std::cout << m1 + m2;
    std::cout << m1 - m2;
    std::cout << m1 * m2;
    std::cout << m1 * 3;
    std::cout << m1 / 3;
    std::cout << m1.exponent(m1,5);
    m1.info();
    return 0;
}