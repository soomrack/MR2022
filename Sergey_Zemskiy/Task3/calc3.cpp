#include <iostream>
#include <algorithm>


using namespace std;// везде

class Matrix {

private:
    unsigned int rows;
    unsigned int columns;
    double* values;

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
    void set_values (const double* array);


    void print () ; // Вывод матрицы
    void feeling() ; // Заполнение матрицы


    Matrix operator=(const Matrix& other); // Оператор присваивания
    Matrix& operator=( Matrix&& other); // Оператор переноса
    Matrix operator+=(const Matrix& M1);
    Matrix operator*=(const Matrix& M1);
    Matrix operator+(const Matrix& M1);
    Matrix operator-(const Matrix& M1);
    Matrix operator*(const Matrix& M1) ;
    Matrix operator*(double mult);
    Matrix operator^(unsigned int number);

    Matrix Single ();
    Matrix exp(const unsigned int time);
    Matrix minor(Matrix& M1, unsigned int row, unsigned int col);

    friend bool operator==(const Matrix &M1, const Matrix &M2);
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


Matrix::Matrix(unsigned int rows, unsigned int columns) {
    this->rows = rows;
    this->columns = columns;
    this->values = new double [rows * columns];
    for (unsigned int i = 0; i < (rows * columns); i++) {
        this->values[i] = 0.0;
    }
}

Matrix::Matrix(unsigned int rows) {
    this->rows = rows;
    this->columns = rows;
    this->values = new double [rows * columns];
    for (unsigned int i = 0; i < (rows * columns); i++) {
        values[i] = 0.0;
    }
}

Matrix::Matrix (){
    rows=0;
    columns=0;
    values = nullptr;
    }

Matrix::Matrix(const Matrix &other) { // Конструктор копирования
    this->rows = other.rows;
    this->columns = other.columns;
    this->values = new double[other.rows * other.columns];
    memcpy(values, other.values, rows * columns * sizeof (double ));
}

Matrix::Matrix(Matrix&& other) { // Конструктор переноса
    rows = other.rows;
    columns = other.columns;
    values = other.values;
    other.values = nullptr;
}

Matrix::~Matrix() {
    delete[] values;
}

void Matrix::set_values ( const double* array){
    for (unsigned int number = 0; number < rows * columns; number++) {
        values[number] = array[number];
    }
}

void Matrix::print () {
    for (unsigned int row = 0; row < this->rows; row++){
        for (unsigned int col = 0; col < this->columns; col++){
            cout << values[row * columns + col] << "\t" ;
        }
        cout << "\n" ;
    }
    cout << "\n" ;
}


void Matrix::feeling () {
    for (unsigned int row = 0; row < this->rows; row++){
        for (unsigned int col = 0; col < this->columns; col++){
            values[row * columns + col] = (double)(row * columns + col + 1) ;
        }
    }
}


Matrix Matrix::operator=(const Matrix &other) { // Оператор присваивания
    if (other == *this) return other;
    rows = other.rows;
    columns = other.columns;
    delete[] values;
    values = new double[other.rows*other.columns];
    memcpy(values, other.values, rows * columns * sizeof (double ));
    return *this;
}


Matrix& Matrix::operator=(Matrix &&other) { // Оператор переноса
    if (this == &other) {return *this;}
    rows = other.rows;
    columns = other.columns;
    values = other.values;
    other.values = nullptr;
    return *this;
}


Matrix Matrix::operator+=(const Matrix& M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    for (unsigned int index = 0; index < rows * columns; ++index) {
        this->values[index] += M1.values[index];
    }
    return *this;
}


Matrix Matrix::operator*=(const Matrix& M1) {
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



Matrix Matrix::operator+(const Matrix &M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    Matrix M0(M1);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] += M1.values[i] ;
    }
    return M0;
}


Matrix Matrix::operator-(const Matrix &M1) {
    if ((columns != M1.columns) || (rows != M1.rows)) {
        throw same_size;
    }
    Matrix M0(M1);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] -= M1.values[i] ;
    }
    return M0;
}


Matrix Matrix::operator*(double mult) {
    Matrix M0(*this);
    for (unsigned int i = 0; i < (rows * columns); i++) {
        M0.values[i] *= mult ;
    }
    return M0;
}


Matrix Matrix::operator*(const Matrix &M1) {
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


Matrix Matrix::operator^(unsigned int number)  {
    if (columns != rows)  {
        throw square;
    }
    Matrix M0(*this);
    if (number == 0) {
        M0.Single();
        return M0;
    }
    if (number == 1) {
        return M0;
    }
    const Matrix Ms(*this);
    for (unsigned int count = 1; count < number; count++){
        M0 = M0 * Ms;
    }
    return M0;
}


Matrix Matrix:: Single ( ) {
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


Matrix Matrix::exp( const unsigned int time ){
    if (columns != rows)  {
        throw square;
    }
    Matrix M0(*this);
    Matrix Ms(this->rows);
    M0.Single();
    Ms.Single();
    double factorial = 1;
    for (int step = 1; step <= time; step++) {
        factorial *= step;
        Ms *= (*this);
        M0 += (Ms * (1.0 / factorial));
    }
    return M0;
}


Matrix Matrix::minor(Matrix& M1, unsigned int row, unsigned int col) {
    Matrix M0 = Matrix(row - 1, col - 1);
    unsigned int k = 0;
    for (unsigned int count = 0; count < rows * columns; count++){
        if ((count % columns == col) || (count % columns == row)) continue;
        M0.values[k] = M1.values[count];
        k++;
    }
    return M0;
}


bool operator==(const Matrix &M1, const Matrix &M2) {
    if ((M1.columns != M2.columns) || (M1.rows != M2.rows)) {
        throw same_size;
    }
    for (unsigned int number = 0; number <M1.rows * M1.columns; number++) {
        if (M1.values[number] != M2.values[number]) return false ;
    }
    return true;
}


int main() {
    Matrix A(3);
    A.feeling();
    cout << "A" << endl;
    A.print();
    Matrix B(3,3);
    B.feeling();
    cout << "B" << endl;
    B.print();
    cout << "A + B" << endl;
    Matrix C = A + B;
    C.print();
    cout << "A - B" << endl;
    Matrix D = A - B;
    D.print();
    cout << "A * 1.1" << endl;
    Matrix E = A * 1.1;
    E.print();
    cout << "A * B" << endl;
    Matrix F = A * B;
    F.print();
    cout << "A ^ 3" << endl;
    Matrix G = A ^ 3;
    G.print();
    cout << "Single(3)" << endl;
    Matrix H (A.get_columns());
    H.Single();
    H.print();
    cout << "exp(A)" << endl;
    Matrix K = A.exp(3);
    K.print();

    return 0;
}
