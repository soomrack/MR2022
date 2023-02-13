#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <cstring>

template<typename T>

class Matrix {

private:
    unsigned int rows;
    unsigned int columns;
    T *values;

public:
    Matrix (unsigned int rows, unsigned int columns) ; //  Конструктор
    Matrix (unsigned int rows) ;
    Matrix (); //  Конструктор по умолчанию
    Matrix(const Matrix &other) ;  //  Конструктор копирования
    Matrix( Matrix &&other) ; //  Конструктор переноса
    ~Matrix() ; // Деструктор


    void set_rows (int rows) { this->rows=rows; };
    int get_ows () { return rows; };
    void set_columns (int columns) { this->columns=columns; };
    int get_columns () { return columns;};
    void set_values (const T* array);


    void print () ; // Вывод матрицы
    void feeling() ; // Заполнение матрицы


    Matrix<T> operator=(const Matrix& other); // Оператор присваивания
    Matrix<T>& operator=( Matrix&& other); // Оператор переноса
    Matrix<T> operator+=(const Matrix& M1);
    Matrix<T> operator*=(const Matrix& M1);
    Matrix<T> operator+(const Matrix& M1);
    Matrix<T> operator-(const Matrix& M1);
    Matrix<T> operator*(const Matrix& M1) ;
    Matrix<T> operator*(double mult);
    Matrix<T> operator^(unsigned int number);

    Matrix<T> Single ();
    Matrix<T> exp(const unsigned int time);
    Matrix<T> minor(Matrix& M1, unsigned int row, unsigned int col);

    friend bool operator==(const Matrix<T> &M1, const Matrix<T> &M2);
};


class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char* const message) : std::domain_error(message)
    {}
};

Matrix_Exception square("Matrix must be square");
Matrix_Exception row_col("Matrix1 column must be the same size as Matrix2 rows\n");
Matrix_Exception same_size("Matrices must be the same size\n");

template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns) {
    this->rows = rows;
    this->columns = columns;
    this->values = new double [rows * columns];
    for (unsigned int i = 0; i < (rows * columns); i++) {
        this->values[i] = 0.0;
    }
}

template <typename T>
Matrix<T>::Matrix(unsigned int rows) {
    this->rows = rows;
    this->columns = rows;
    this->values = new T [rows * columns];
    for (unsigned int i = 0; i < (rows * columns); i++) {
        values[i] = 0.0;
    }
}

template <typename T>
Matrix<T>::Matrix (){
    rows=0;
    columns=0;
    values = nullptr;
    }

template <typename T>
Matrix<T>::Matrix(const Matrix &other) { // Конструктор копирования
    this->rows = other.rows;
    this->columns = other.columns;
    this->values = new T[other.rows * other.columns];
    memcpy(values, other.values, rows * columns * sizeof (double ));
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) { // Конструктор переноса
    rows = other.rows;
    columns = other.columns;
    values = other.values;
    other.values = nullptr;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] values;
}


template <typename T>
void Matrix<T>::set_values ( const T* array){
    for (unsigned int number = 0; number < rows * columns; number++) {
        values[number] = array[number];
    }
}

template <typename T>
void Matrix<T>::print () {
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < columns; col++){
            std::cout << values[row * columns + col] << "\t" ;
        }
        std::cout << "\n" ;
    }
    std::cout << "\n" ;
}

template <typename T>
void Matrix<T>::feeling () {
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < columns; col++){
            values[row * columns + col] = (T)(row * columns + col + 1) ;
        }
    }
}


template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> &other) { // Оператор присваивания
    if (other == *this) return other;
    rows = other.rows;
    columns = other.columns;
    delete[] values;
    values = new double[other.rows*other.columns];
    memcpy(values, other.values, rows * columns * sizeof (T));
    return *this;
}


template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix &&other) { // Оператор переноса
    if (this == &other) {return *this;}
    rows = other.rows;
    columns = other.columns;
    values = other.values;
    other.values = nullptr;
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator+=(const Matrix<T>& M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    for (unsigned int index = 0; index < rows * columns; ++index) {
        this->values[index] += M1.values[index];
    }
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::operator*=(const Matrix<T>& M1) {
    if (columns != M1.rows)  {
        throw row_col;
    }
    Matrix M0(this->rows);
    for (unsigned int row = 0; row < M0.rows; row++) {
        for (unsigned int col = 0; col < M0.columns; col++) {
            double sum = 0;
            for (unsigned int k = 0; k < M0.rows; k++) {
                sum += values[row * columns + k] * M1.values[k * M1.columns + col];
            }
            M0.values[row * M0.columns + col] = sum;
        }
    }
    *this = M0;
    return (*this);
}



template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    Matrix M0(M1);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] += M1.values[i] ;
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> &M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    Matrix M0(M1);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] -= M1.values[i] ;
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(double mult) {
    Matrix M0(*this);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] *= mult ;
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &M1) {
    if (columns != M1.rows)  {
        throw row_col;
    }
    Matrix M0(rows,M1.columns);
    for (unsigned int row = 0; row <M0.rows; row++) {
        for (unsigned int col = 0; col < M0.columns; col++) {
            M0.values[row * M0.columns + col] = 0.00;
            for (unsigned int k = 0; k < M0.columns; k++) {
                M0.values[row * M0.columns + col] += values[row * columns + k] * M1.values[k * M0.columns + col];
            }
        }
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>::operator^(unsigned int number)  {
    if (columns != rows)  throw square;
    Matrix M0(*this);
    if (number == 0) {
        M0.Single();
        return M0;
    }
    if (number == 1) return M0;
    const Matrix Ms(*this);
    for (unsigned int count = 1; count < number; count++){
        M0 = M0 * Ms;
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>:: Single ( ) {
    if (columns != rows)  {
        throw square;
    }
    for (unsigned int row = 0; row <rows; row++) {
        for (unsigned int col = 0; col < columns; col++) {
            values[row * rows + col] = (row == col) ? 1.0 : 0.0;
        }
    }
    return *this;
}


template <typename T>
Matrix<T> Matrix<T>::exp( const unsigned int time ){
    if (columns != rows)  {
        throw square;
    }
    Matrix<T> M0(this->rows);
    Matrix<T> Ms(this->rows);
    M0.Single();
    Ms.Single();
    double factorial = 1;
    for (int step = 1; step <= time; step++) {
        factorial *= step;
        Ms *= (*this);
        Ms *= (1.0 / factorial);
        M0 += (Ms);
    }
    return M0;
}


template <typename T>
Matrix<T> Matrix<T>::minor(Matrix<T>& M1, unsigned int row, unsigned int col) {
    Matrix M0 = Matrix(row - 1, col - 1);
    unsigned int k = 0;
    for (unsigned int count = 0; count < rows * columns; count++){
        if ((count % columns == col) || (count % columns == row)) continue;
        M0.values[k] = M1.values[count];
        k++;
    }
    return M0;
}

template <typename T>
bool operator==(const Matrix<T> &M1, const Matrix<T> &M2) {
    if ((M1.columns != M2.columns) || (M1.rows != M2.rows)) {
        throw same_size;
    }
    for (unsigned int number = 0; number <M1.rows * M1.columns; number++) {
        if (M1.values[number] != M2.values[number]) return false ;
    }
    return true;
}


template <typename T>
class Matrix_Mem : public Matrix<T> {
protected:
    unsigned int mem_size;
    static unsigned int quantity;
    static unsigned int total_memory;

public:
    Matrix_Mem();
    Matrix_Mem(const unsigned int n);
    Matrix_Mem(const unsigned int row, unsigned int col);
    Matrix_Mem(const Matrix_Mem<T> &x);
    Matrix_Mem(Matrix_Mem<T> &&x);
    ~Matrix_Mem();

    Matrix_Mem<T>& operator=(const Matrix_Mem<T> &other);
    Matrix_Mem<T>& operator=(Matrix_Mem<T> &&other);
    Matrix_Mem<T>& operator*=(const Matrix_Mem<T> &other);

    void print();

    static int get_quantity() { return quantity; }
    static int get_mem() { return total_memory; }
};

template <typename T>
unsigned int Matrix_Mem<T>::total_memory = 0;
template <typename T>
unsigned int Matrix_Mem<T>::quantity = 0;

template <typename T>
Matrix_Mem<T>::Matrix_Mem():Matrix<T>(){
    mem_size = 0;
    quantity++;
    total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(const unsigned int n):Matrix<T>(n){
    mem_size = n * n * sizeof (T);
    quantity++;
    total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(const unsigned int row, unsigned int col):Matrix<T>(row, col){
    mem_size = row * col * sizeof (T);
    quantity++;
    total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(const Matrix_Mem<T> &other):Matrix<T>(other){
    mem_size = other.mem_size;
    quantity++;
    total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::Matrix_Mem(Matrix_Mem<T> &&other):Matrix<T>(other){
    total_memory -= mem_size;
    mem_size = other.mem_size;
    other.mem_size = 0;
    total_memory += mem_size;
}

template <typename T>
Matrix_Mem<T>::~Matrix_Mem(){
    quantity--;
    total_memory -= mem_size;;
}

template<typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator=(const Matrix_Mem<T> &other) {
    if (other == *this) return other;
    this->rows = other.rows;
    this->columns = other.columns;
    delete[] this->values;
    this->values = new double[other.rows * other.columns];
    memcpy(this->values, other.values, this->rows * this->columns * sizeof(T));
    return *this;
}

template<typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator=(Matrix_Mem<T> &&other) {
    if (this == &other) {return *this;}
    this->rows = other.rows;
    this->columns = other.columns;
    this->values = other.values;
    other.values = nullptr;
    mem_size = other.mem_size;
    total_memory += mem_size;
    return *this;
}

template <typename T>
Matrix_Mem<T>& Matrix_Mem<T>::operator*=(const Matrix_Mem<T> &other) {
    if (this->columns != this->M1.rows)  {
        throw row_col;
    }
    Matrix_Mem M0(this->rows);
    for (unsigned int row = 0; row < M0.rows; row++) {
        for (unsigned int col = 0; col < M0.columns; col++) {
            double sum = 0;
            for (unsigned int k = 0; k < M0.rows; k++) {
                sum += this->values[row * this->columns + k] * other.values[k * other.columns + col];
            }
            M0.values[row * M0.columns + col] = sum;
        }
    }
    *this = M0;
    return (*this);
}

template <typename T>
void Matrix_Mem<T>::print() {
    std::cout << "variable weight is " << mem_size << std::endl ;
    std::cout << "Number of variables " << get_quantity() << std::endl;
    std::cout << "Total memory used " << get_mem() << std::endl;
}

int main() {
    Matrix_Mem<double> A(3);
    A.feeling();
    std::cout << "A" << std::endl;
    A.print();
    Matrix_Mem<double> B(3,3);
    B.feeling();
    std::cout << "B" << std::endl;
    B.print();
    std::cout << "A + B" << std::endl;
    Matrix<double> C = A + B;
    C.print();
    std::cout << "A - B" <<std::endl;
    Matrix<double> D = A - B;
    D.print();
    std::cout << "A * 1.1" <<std::endl;
    Matrix<double> E = A * 1.1;
    E.print();
    std::cout << "A * B" << std::endl;
    Matrix<double> F = A * B;
    F.print();
    std::cout << "A ^ 3" << std::endl;
    Matrix<double> G = A ^ 3;
    G.print();
    std::cout << "Single(3)" << std::endl;
    Matrix<double> H (A.get_columns());
    H.Single();
    H.print();
    std::cout << "exp(A)" << std::endl;
    Matrix<double> K = A.exp(3);
    K.print();

    return 0;
}
