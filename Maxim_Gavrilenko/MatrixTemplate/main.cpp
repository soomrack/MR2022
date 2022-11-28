#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include <typeinfo>

const double EPS = 0.0000001;

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const msg) : std::domain_error(msg)
    {}
};


Matrix_Exception NOTSQUARE("Error:the matrix must be square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have a same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory are not allocated\n");

template<typename T>
class Matrix {
protected:
    unsigned int rows;
    unsigned int cols;
    T *values;
public:

    //Constructors
    Matrix(unsigned int, unsigned int, T *);
    Matrix(unsigned int, unsigned int);
    Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&) noexcept;
    //Destructor
    ~Matrix();
    //Methods
    unsigned int getrow();
    unsigned int getcol();
    void output();
    void fill_random(unsigned int n);
    void set_zero();
    void set_identity();
    Matrix set_transpose();
    Matrix fill_from_array(T*);
    double determinant(const Matrix<T>, unsigned int);
    Matrix reverse(const Matrix<T>, const unsigned int);
    Matrix minor(const Matrix<T>, const unsigned, const unsigned, const unsigned);
    Matrix exponent(unsigned int);
    //Overload operator
    bool operator!=(const Matrix<T>&);
    bool operator==(const Matrix<T>&);
    Matrix& operator=(const Matrix<T>&);
    Matrix& operator-=(const Matrix<T>&);
    Matrix& operator+=(const Matrix<T>&);
    Matrix& operator*=(const Matrix<T>&);
    Matrix& operator*=(const T);
    Matrix& operator/=(const T);
    //Overload operator +, -, =,/,*
    Matrix<T> operator+ (const Matrix<T>&);
    Matrix<T> operator- (const Matrix<T>&);
    Matrix<T> operator* (const Matrix<T>&);
    Matrix<T> operator* (const T);
    Matrix<T> operator/ (const T);
    friend std::ostream& operator<<(std::ostream& out, Matrix<T> matrix)
    {
        {
            for (unsigned int row = 0; row < matrix.rows; row++)
            {
                for (unsigned int col = 0; col < matrix.cols; col++)
                {
                    out << matrix.values[row * matrix.cols + col] << "\t";
                }
                out << std::endl;
            }
            out << std::endl;
            return(out);
        }
    }
};
    template <typename T>
    Matrix<T>::Matrix(unsigned int num_row, unsigned int num_col, T* value)
    {
        rows = num_row;
        cols = num_col;
        values = new T[rows * cols];
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            values[idx] = value[idx];
        }
    }
    template <typename T>
    Matrix<T>::Matrix(unsigned int num_row, unsigned int num_col)
    {
        rows = num_row;
        cols = num_col;
        values = new T[rows * cols];
        if (!values) throw MEM_ERROR;
    }

    template <class T>
    Matrix<T>::Matrix(Matrix&& mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols)
    {
        mat.values = nullptr;
        mat.rows = 0;
        mat.cols = 0;
    }

    template <class T>
    Matrix<T>::Matrix() : rows(0), cols(0), values(nullptr) {}

    template <class T>
    Matrix<T>::Matrix(const Matrix& mat) : rows(mat.rows), cols(mat.cols)
    {
    values = new double[rows * cols];
    /*if (!values) throw MEM_ERROR;*/
    memcpy(values, mat.values, rows * cols * sizeof(double));
    }

    template <typename T>
    Matrix<T>::~Matrix()
    {
        if (values != nullptr) {
            delete[] values;
        }
    }

    template <typename T>
    unsigned int Matrix<T>::getrow()
    {
        return (rows);
    }

    template <typename T>
    unsigned int Matrix<T>::getcol()
    {
        return (cols);
    }

    template <typename T>
    void Matrix<T>::set_zero() {
        for (unsigned int idx = 0; idx < this->rows * this->cols; idx++) {
            this->values[idx] = 0;
        }
    }

    template <typename T>
    void Matrix<T>::set_identity() {
        set_zero();
        for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1) {
            this->values[idx] = 1.0;
        }
    }

    template <typename T>
    Matrix<T> Matrix<T>::set_transpose()
    {
        Matrix trans(this->cols, this->rows);
        for (unsigned int row = 0; row < trans.rows; row++) {
            for (unsigned int col = 0; col < trans.cols; col++) {
                trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
            }
        }
        *this = trans;
        return *this;
    }

    template <typename T>
    bool Matrix<T>::operator==(const Matrix<T> &A)
    {
        if (this->cols != A.cols || this->rows != A.rows) return false;
        for (unsigned int idx = 0; idx < this->cols * this->rows; idx++) {
            if (abs(this->values[idx] - A.values[idx]) > EPS) return false;
        }
        return true;
    }

    template <typename T>
    bool Matrix<T>::operator!=(const Matrix<T>& mat)
    {
        return !(*this == mat);
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator=(const Matrix& A)
    {
        if (this == &A) return *this;
        delete[] values;
        rows = A.rows;
        cols = A.cols;
        this->values = new double[rows * cols];
        if (!values) throw MEM_ERROR;
        memcpy(this->values, A.values, rows * cols * sizeof(double));
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& matrix)
    {
        if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;
        for (unsigned int index = 0; index < rows * cols; ++index) {
            this->values[index] += matrix.values[index];
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& matrix)
    {
        if (rows != matrix.rows || cols != matrix.cols) throw NOTEQUAL;
        for (unsigned int index = 0; index < rows * cols; ++index) {
            this->values[index] -= matrix.values[index];
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& matrix)
    {
    if (cols != matrix.rows) throw MULTIPLYERROR;
    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++) {
        for (unsigned int col = 0; col < multiplication.cols; col++) {
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++) {
                sum += values[row * cols + k] * matrix.values[k * matrix.cols + col];
            }
            multiplication.values[row * multiplication.cols + col] = sum;
        }
    }
    *this = multiplication;
    return (*this);
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator*=(const T k) // Умножение матрицы на число
    {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            this->values[idx] *= k;
        }
        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator/=(const T k) // Деление матрицы на число
    {
        for (unsigned int idx = 0; idx < rows * cols; idx++) {
            this->values[idx] /= k;
        }
        return *this;
    }

    template <typename T>
        Matrix<T> Matrix<T>::operator+(const Matrix<T>& matrix)
        {
            Matrix add(*this);
            add += matrix;
            return (add);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T>& matrix)
    {
        Matrix sub(*this);
        sub -= matrix;
        return (sub);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const Matrix<T>& matrix)
    {
        Matrix multiply(*this);
        multiply *= matrix;
        return (multiply);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator*(const T value)
    {
        Matrix multiply(*this);
        multiply *= value;
        return (multiply);
    }

    template <typename T>
    Matrix<T> Matrix<T>::operator/(const T value)
    {
        Matrix multiply(*this);
        multiply /= value;
        return (multiply);
    }
    template<typename T>
    void Matrix<T>::output()
    {
            for (unsigned int row = 0; row < rows; row++)
            {
                for (unsigned int col = 0; col < cols; col++)
                {
                    std::cout << values[row * cols + col] << "\t";
                }
                std::cout << std::endl;
            }
    }

    template<typename T>
    void Matrix<T>::fill_random(unsigned int n /*Максимальное значение*/)
    {
        for (unsigned int index = 0; index < cols * rows; index++) {
            values[index] = T(rand() % n);
        }
    }

template <typename T>
Matrix<T> Matrix<T>::minor(const Matrix matrix, const unsigned int size, const unsigned int row, const unsigned int col)
{
    Matrix minor(size - 1, size - 1);
    unsigned int shiftrow = 0; //Смещение индекса строки в матрице
    unsigned int shiftcol; //Смещение индекса столбца в матрице
    for (unsigned int rows = 0; rows < size - 1; rows++) {
        //Пропустить row-ую строку
        if (rows == row) { shiftrow = 1; } //Как только встретили строку,
        //которую надо пропустить, делаем смещение для исходной матрицы
        shiftcol = 0; //Обнулить смещение столбца
        for (unsigned int cols = 0; cols < size - 1; cols++) {
            if (cols == col) { shiftcol = 1; }
            minor.values[rows * (size - 1) + cols] = matrix.values[(rows + shiftrow)
                                                                   * size + (cols + shiftcol)];
        }
    }
    return minor;
}

template <typename T>
double Matrix<T>::determinant(const Matrix matrix, unsigned int size)
{
    if (matrix.rows != matrix.cols) throw NOTSQUARE;
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
        det += k * matrix.values[idx] * determinant(minor(matrix, size, 0, idx), size - 1);
        k = -k;
    }
    return det;
}

template <typename T>
Matrix<T> Matrix<T>::reverse(const Matrix matrix, const unsigned int size) // Функция нахождения обратной матрицы
{
    double d = determinant(matrix, size);
    if (matrix.rows != matrix.cols) throw NOTSQUARE;
    Matrix reverse(matrix.rows, matrix.cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++) {
        for (unsigned int col = 0; col < reverse.cols; col++) {
            reverse.values[row * size + col] = k * determinant(minor(matrix, size, row, col), size - 1);
            k = -k;
        }
    }
    reverse.set_transpose();
    if (fabs(d) < EPS) throw ZERODIVISION;
    reverse /= d;
    return reverse;
}

template <typename T>
Matrix<T> Matrix<T>::exponent(unsigned int n /*Количество членов разложения*/)
{
    if (rows != cols) throw NOTSQUARE;
    Matrix ex(rows, cols);
    Matrix temp(rows, cols);
    temp.set_identity();
    ex.set_identity();
    double fact = 1.0;
    for (unsigned int i = 1; i < n; i++) {
        fact *= i;
        temp *= (*this);
        ex += temp / fact;
    }
    return ex;
}

template <typename T>
Matrix<T> Matrix<T>::fill_from_array(T* array)
{
    memcpy(values, array, rows * cols * sizeof(double));
}

template <typename T1>
class Matrix_Memory: public Matrix<T1>
{
private:
        T1 memory;
public:
    Matrix_Memory(T1* A): Matrix<T1>()
    {
    this->memory = A;
    };
    void memory_size()
    {
        std::cout << "Memory for object class - " << sizeof(memory) * this->rows * this -> cols << std:: endl;
    }
    void type_name()
    {
        std::cout <<"Type name: - " << typeid(memory).name() << std::endl;
    }
};
    int main() {
        try { // Проверка выделения памяти
            Matrix<double> A = Matrix<double>(0, 0);
        }
        catch (const Matrix_Exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
            exit(404);
        }
        Matrix<double> A(20,19);
        A.fill_random(10);
        Matrix<double> B(3,3);
        B.fill_random(10);
        std::cout << "First Matrix\n" << A;
        std::cout << "Second Matrix\n" << B;

        try {
            std::cout << "Addiction of two matrix\n" << A + B;
            std::cout << "Subtraction of two matrix\n" << A - B;

        }
        catch (const Matrix_Exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
        try {
            std::cout << "Multiplication of two matrix\n" << A * B;
        }
        catch (const Matrix_Exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }

        try {
            std::cout << "Determinant\n" << A.determinant(A, A.getrow()) << std::endl;
            std::cout << "Reverse Matrix\n" << A.reverse(A, A.getrow()) << std::endl;
            std::cout << "Exponent Matrix\n" << A.exponent(30);
        }
        catch (Matrix_Exception &e) {
            std::cerr << "Caught: " << e.what() << std::endl;
            std::cerr << "Type: " << typeid(e).name() << std::endl;
        }
    }