#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <exception>

double DELTA = 0.0000001;

template<typename T1>
class Matrix_Exception {
public:
    T1 kod_mistake;

    Matrix_Exception();
    Matrix_Exception(T1 kod_mistake);
    //~Matrix_Exception() ;

    void set_mistake (T1 kod_mistake);
};


//Объявление исключений
Matrix_Exception different_sizes=(1);
Matrix_Exception not_square=(2);
Matrix_Exception cannot_be_multiplied=(3);
Matrix_Exception determinant_is_zero=(4);
Matrix_Exception dimensions_negative = 0;



//Операторы класса иcключений
template<typename T1>
Matrix_Exception<T1>:: Matrix_Exception(){
    kod_mistake = 999;
}

template<typename T1>
Matrix_Exception<T1>:: Matrix_Exception(T1 kod){
    kod_mistake = kod;
}

template<typename T1>
void Matrix_Exception<T1>::set_mistake (T1 error){
    switch (error) {
        case 1:
            std::cout << "\n"<< "       Matrix data of different sizes \n"<< "\n";
            break;
        case 2:
            std::cout<< "\n" << "       The matrix is not square \n"<< "\n";
            break;
        case 3:
            std::cout<< "\n" << "       Matrix data cannot be multiplied \n"<< "\n";
            break;
        case 4:
            std::cout<< "\n" << "       Matrix determinant is zero \n"<< "\n";
            break;
        case 0:
            std::cout<< "\n" << "       Matrix dimensions are negative \n"<< "\n";
            break;
        default:
            std::cout << "       Unknown error \n";
    }
}

template<class T2> // сделай приватными
class Matrix {
protected:
    unsigned int rows;
    unsigned int cols;
    T2* line;
    T2** massive;
public:

    unsigned int getrow();
    unsigned int getcol();
    T2* getline();

// Конструкторы и деструкторы класса
    Matrix();  // условный конструктор ( с пустыми параметрами)
    Matrix(const unsigned int row, const unsigned int col);  //конструктор с двямя параметрами
    Matrix( const unsigned int number); // конструктор с одним параметром
    Matrix(const Matrix& A);  // оператор копирования
    Matrix(Matrix&& A);  // оператор переноса
    ~Matrix();  // деструктор

//Операторы класса
    Matrix& operator=(const Matrix &X);
    Matrix& operator+=(const Matrix &X);
    Matrix& operator-=(const Matrix &X);
    Matrix& operator*=(const double k);
    Matrix& operator*=(const Matrix &X);
    bool operator==(const Matrix &X);

    Matrix operator+ (const Matrix &X);
    Matrix operator- (const Matrix &X);
    Matrix operator* (const Matrix &X);
    Matrix operator* (const double k);






//Методы класса
    Matrix empty();
    Matrix zero();
    Matrix indentity();
    Matrix addition(const Matrix X);
    Matrix subtraction (const Matrix X);
    Matrix multiplication (const Matrix X);
    Matrix multiplication (double k);
    Matrix minor ( unsigned int x, unsigned int y);
    double determinant ();
    void output();
    Matrix pow (const Matrix X, unsigned int k);
    Matrix inverce ();
    Matrix transposition ();
};
template<class T2>
class Memory_Matrix: protected Matrix <T2>{


};


template<class T2>
void test(const Matrix<T2> A, const Matrix<T2> B);
template<class T2>
void test_add (const Matrix<T2> X, const Matrix<T2> Y);
template<class T2>
void test_sub (const Matrix<T2> X, const Matrix<T2> Y);
template<class T2>
void test_mult (const Matrix<T2> X, const Matrix<T2> Y);
template<class T2>
void test_exp (const Matrix<T2> X, const Matrix<T2> Y);
template<class T2>
void test_inv (const Matrix<T2> X, const Matrix<T2> Y);
template<class T2>


unsigned int min (unsigned int a, unsigned int b);
double factorial (unsigned int k);

template<class T2>
unsigned int Matrix<T2>::getrow() {  // показать строку
    return (rows);
}

template<class T2>
unsigned int Matrix<T2>::getcol() {  // показать столбец
    return (cols);
}


template<class T2>
T2* Matrix<T2>::getline(){  // показыть линию
    return (line);
}


//Описание конструкторов и деструкторов
template<class T2>
Matrix<T2>:: Matrix() {  // условный конструктор
    rows = 0;
    cols = 0;
    line = nullptr;
    massive = nullptr;
}

template<class T2>
Matrix<T2>:: Matrix (unsigned int row, unsigned int col) {  //конструктор с двумя параметрами
    if (row < 0 || col < 0) {
        try{ throw dimensions_negative;}
        catch (Matrix_Exception<int> error){ error.set_mistake(0);}
    }
    rows = row;
    cols = col;
    line = new T2[row * col];
    massive = new T2*[rows];
    for (unsigned int number = 0; number < rows; number++) {
        massive[number] = line + cols * number;
    }
}

template<class T2>
Matrix<T2>:: Matrix (unsigned int number) {  //конструктор с одним параметром
    if (number < 0 ) {
        try{ throw dimensions_negative;}
        catch (Matrix_Exception<int> error){ error.set_mistake(0);}
    }
    rows = number;
    cols = number;
    line = new T2[number * number];
    massive = new T2 *[number];
    for (unsigned int i = 0; i < number; i++) {
        massive[i] = line + number * i;
    }
}
template<class T2>
Matrix<T2>:: Matrix (const Matrix<T2>&A){  //конструктор копирования
    cols = A.cols;
    rows = A.rows;
    line = new T2[rows * cols];
    for (unsigned int number = 0; number < rows * cols; number++) {
        line[number] = A.line[number];
    }
    massive = new T2*[cols] {nullptr};
    for (std::size_t i = 0; i < cols; ++i) {
        massive[i] = line + cols * i;
    }
}

template<class T2>
Matrix<T2>:: Matrix ( Matrix<T2> &&obj) {  //конструктор переноса
    if(&obj != this) {
        rows = obj.rows;
        cols = obj.cols;
        line = obj.line;
        massive = obj.massive;
        obj.rows = 0;
        obj.cols = 0;
        obj.line = nullptr;
        obj.massive = nullptr;
    }
}

template<class T2>
Matrix<T2>:: ~Matrix() {  // деструктор
    delete[] line;
    delete[] massive;
}

//Описание операторов
template<class T2>
Matrix<T2>& Matrix<T2>::operator=(const Matrix<T2> &X) {  // работает
    if (this == &X) {
        return *this;
    }
    delete[] this->line;
    delete[] this->massive;
    rows = X.rows;
    cols = X.cols;
    this->line = new T2[rows * cols];
    for (unsigned int number = 0; number < rows * cols; number++) {
        this->line[number] = X.line[number];
    }
    massive = new T2 *[cols]{nullptr};
    for (std::size_t i = 0; i < cols; ++i) {
        massive[i] = line + cols * i;
    }
}

template<class T2>
Matrix<T2> &Matrix<T2>::operator+=(const Matrix<T2> &X) {
    if ((rows != X.rows) or (cols != X.cols)) {
        throw different_sizes;
        return *this;
    }
    for (unsigned int number = 0; number < rows * cols; number++) {
        line[number] += X.line[number];
    }
    return *this;
}

template<class T2>
Matrix<T2>& Matrix<T2>:: operator-=(const Matrix &X){
    if ((rows != X.rows) or (cols != X.cols)) {
        throw different_sizes;
        return *this;
    }
    for (unsigned int number = 0; number < rows * cols; number++){
        line[number] -= X.line[number];
    }
    return *this;
}

template<class T2>
Matrix<T2>& Matrix<T2>:: operator*=(const double k){
    for (unsigned int number = 0; number < rows * cols; number++){
        line[number] *= k;
    }
    return *this;
}

template<class T2>
Matrix<T2>& Matrix<T2>:: operator*=(const Matrix &X) {
    if (cols != X.rows) {
        throw cannot_be_multiplied;
        return *this;
    }
    for (unsigned int row = 0; row < X.rows; row++) {
        for (unsigned int col = 0; col < cols; col++) {
            for (unsigned int number = 0; number < X.cols; number++)
                massive[row][col] = X.massive[row][number] * massive[number][col];
        }
    }
    return *this;
}

template<class T2>
bool Matrix<T2>:: operator==(const Matrix<T2> &X) {  // работает
    if (this->cols != X.cols || this->rows != X.rows) return false;
    for (unsigned int number = 0; number < this->cols * this->rows; number++) {
        if (abs(this->massive[number] - X.massive[number]) > DELTA) return false;
    }
    return true;
}

template<class T2>
Matrix<T2> Matrix<T2>:: operator +(const Matrix<T2> &X) {  //работает
    if (rows != X.rows || cols != X.cols){
        throw different_sizes;
        return empty<T2>();
    }
    Matrix summa = Matrix(rows, cols);
    for (unsigned int number = 0; number < summa.cols * summa.rows; number++) {
        summa.line[number] = line[number] + X.line[number];
    }
    return summa;
}

template<class T2>
Matrix<T2> Matrix<T2>:: operator-(const Matrix<T2> &X) {  //работает
    if (rows != X.rows || cols != X.cols) {
        throw different_sizes;
        return empty<T2>();
    }
    Matrix minys = Matrix(rows, cols);
    for (unsigned int number = 0; number < minys.cols * minys.rows; number++) {
        minys.line[number] = line[number] - X.line[number];
    }
    return minys;
}

template<class T2>
Matrix<T2> Matrix<T2>:: operator*( const Matrix<T2> &X) {  // работает
    if (cols != X.rows) {
        throw cannot_be_multiplied;
       // return empty<T2>();
    }
    Matrix res = Matrix<T2>(rows, X.cols); //
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.massive[row][col] = 0;
            for (unsigned int h = 0; h < cols; h++) {
                res.massive[row][col] += massive[row][h] * X.massive[h][col];
            }
        }
    }
    return res;
}

template<class T2>
Matrix<T2> Matrix<T2>:: operator*(double k ) {
    Matrix  res = Matrix<T2> ( rows, cols);
    for (unsigned int number = 0; number < cols * rows; number++){
        res.line[number] = line [number] * k;
    }
    return res;
}

template<class T2>
Matrix<T2> operator^(const Matrix<T2> &X, const double step){
    Matrix help = X;
    Matrix power = Matrix<T2> (help.getrow(), help.getcol());
    power = power.indentity();
    if (step == 0) return power;
    for (unsigned int i = 1; i <= step; i++){
        power = help * power;
    }

    return power;

}

template<class T2>
Matrix<T2>  operator%(const Matrix<T2> &X,const double step){
    Matrix help = X;
    if(help.getcol() != help.getrow()) {
        throw not_square;
        //return empty<T2>();
    }
    Matrix result_exp = Matrix<T2>(help.getrow(), help.getcol());
    result_exp = X;
    double factor = 0.5;
    for(int unsigned i = 2; i <= step; i++) {
        Matrix power = X ^ i;
        Matrix fact = power.multiplication(factor);
        result_exp = result_exp.addition(fact);
        factor = 1 / factorial(i+1);
    }
    Matrix result = result_exp.addition(result_exp.indentity());
    return result ;
}


// Описание методов
template<class T2>
Matrix<T2> Matrix<T2>:: empty(){
    Matrix empty = Matrix<T2>();
    return empty;
}


double factorial (unsigned int k){
    if(k == 1) return 1.00;
    if(k == 2) return 2.00;
    double result = 1.00;
    for (int i = 1; i <= k; i++){
        result *= i;
    }
    return result;
}

inline unsigned int min (unsigned int a, unsigned int b){
    return  ((a > b) ?  a:  b);
}


template<class T2>
Matrix<T2> Matrix<T2>::addition ( const Matrix X) {
    if ((rows != X.rows) || (cols != X.cols)) {
        throw different_sizes;
       // return empty<T2>();
    }
    Matrix result = Matrix(rows, cols);
    for (unsigned int number = 0; number < result.rows * result.cols; number++) {
        result.line[number] = line[number] + X.line[number];
    }
    return result;
}

template<class T2>
Matrix<T2> Matrix<T2>::subtraction ( const Matrix X){
    if( (rows != X.rows) || (cols != X.cols)){
        throw different_sizes;
        //return empty<T2>();
    }
    Matrix result = Matrix(rows , cols);
    for (unsigned int number=0 ; number < result.rows * result.cols; number++){
        result.line[number] = line[number] - X.line[number];
    }
    return result;
}

template<class T2>
Matrix<T2> Matrix<T2>::multiplication(double k) {
    Matrix result = Matrix(rows, cols);
    for (unsigned int number = 0; number < result.rows  ; number++){
        for( unsigned int i = 0; i< result.cols; i++){
            result.massive [number][i] = massive [number][i] * k;
        }
    }
    return result;
}

template<class T2>
Matrix<T2> Matrix<T2>::minor(const unsigned int cur_row, const unsigned int cur_col){
    int new_row = rows - 1, new_col = cols - 1;
    Matrix  rez = Matrix(new_row, new_col);
    unsigned int k = 0;
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        if ((idx % cols == cur_col) or (idx / cols == cur_row)) continue;
        rez.line[k++] = line[idx];
    }
    return rez;
}

template<class T2>
double Matrix<T2>:: determinant (){
    if (cols != rows){
        throw not_square;
        return 0.00;
    }
    double znak = 1.00;
    if(cols != rows) {
        throw 2;
        return 0.00;
    }
    if(cols == 1){
        return massive[0][0];
    }
    if( cols == 2){
        return massive[0][0] * massive[1][1] - massive[1][0] * massive[0][1];
    }
    double det = 0.00;
    for(unsigned int i = 0; i < cols; i++){
        Matrix minor_auxiliary = minor(0,i);
        det = det + znak * massive[0][i] * minor_auxiliary.determinant();
        znak *= -1.00;
    }
    return det;
}

template<class T2>
Matrix<T2> Matrix<T2>::multiplication(const Matrix X) {
    if (cols != X.rows){
        throw cannot_be_multiplied;
       // return empty<T2>();
    }
    Matrix  res = Matrix ( rows, X.cols); //
    for (unsigned int row = 0; row < res.rows; row++) {
        for (unsigned int col = 0; col < res.cols; col++) {
            res.massive[row][col] = 0;
            for (unsigned int h = 0; h < cols; h++) {
                res.massive[row][col] += massive[row][h] * X.massive[h][col];
            }
        }
    }
    return res;
}

template<class T2>
Matrix<T2> Matrix<T2> ::  zero (){
    Matrix zero = Matrix<T2> (rows, cols);
    for (unsigned int number = 0; number < rows * cols; number ++){
        zero.line[number] = 0.00;
    }
    return zero;
}

template<class T2>
Matrix<T2> Matrix<T2>:: indentity(){
    if (rows !=  cols){
        throw not_square;
       // return empty<T2>();
    }
    Matrix one = Matrix<T2> (rows , cols);
    one = zero ()   ;
    unsigned int minimum = min(rows, cols);
    for (unsigned int  number = 0; number < minimum ; number ++){
        one.massive[number][number] = 1.00;
    }
    return one;
}

template<class T2>
Matrix<T2> Matrix<T2>:: pow(const Matrix X, const unsigned int step){
    if ( X.rows != X.cols){
        try{throw not_square;}
        catch (Matrix_Exception<int> error){
            error.set_mistake(2);
        }
       // return empty<T2>();
    }
    Matrix power = Matrix (X.rows, X.cols);
    power = power.indentity();
    if (step == 0) return power;
    for (unsigned int i = 1; i <= step; i++){
        power = multiplication(power);
    }
    return power;
}

template<class T2>
Matrix<T2> Matrix<T2> ::transposition (){
    Matrix trans = Matrix (cols, rows);
    for (unsigned int row = 0; row < rows; row ++){
        for (unsigned col = 0; col < cols; col ++){
            trans.massive[row][col] = massive [col][row];
        }
    }
    return trans;
}

template<class T2>
Matrix<T2> Matrix<T2>::inverce() {
    if (rows != cols ){
        throw determinant_is_zero;
      //  return empty<T2>();
    }
    double det_A = determinant();
    double znak = 1.00;
    Matrix result = Matrix(rows, cols);
    Matrix result_trans =  Matrix(rows, cols);
    if(fabs(det_A) < DELTA) {
        throw determinant_is_zero;
      //  return empty<T2>();
    }
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            Matrix minor_auxiliary = minor( row, col);
            result.massive[row][col] = znak * minor_auxiliary.determinant() / det_A;
            znak *= -1;
        }
    }
    result_trans = result.transposition();
    return  result_trans;
}


inline void Proverka (bool h){
    if( h = true)  std::cout << " " << "performed correctly  \n";
    else std::cout <<  "  done in error \n";
}

template<class T2>
void  test_add (const Matrix<T2> X, const Matrix<T2> Y){
    Matrix prototype_A = X;
    Matrix prototype_B = Y;
    std::cout << "Addition test";
    try{
        Proverka(prototype_A.addition(prototype_B) == (prototype_B * 2.00));
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(1);
    }
}

template<class T2>
void  test_sub (const Matrix<T2> X, const Matrix<T2> Y){
    Matrix prototype_A = X;
    Matrix prototype_B = Y;
    std::cout << "Subtraction test";
    try{
        Proverka(prototype_B.subtraction(prototype_A) ==  prototype_A.zero());
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(1);
    }
}

template<class T2>
void  test_mult (const Matrix<T2> X, const Matrix<T2> Y){
    Matrix prototype_A = X;
    Matrix prototype_B = Y;
    std::cout << "Multiplication test";
    try{
        Proverka( prototype_A.multiplication(prototype_B.zero()) == prototype_B.zero());
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(3);
    }
}

template<class T2>
void  test_exp (const Matrix<T2> X, const Matrix<T2> Y){
    Matrix<T2> prototype_A = X;
    Matrix<T2> prototype_B = Y;
    std::cout << "Exhibitor";
    try{
        Proverka( prototype_A%2 == prototype_B * 2.5 );
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(2);
    }
}

template<class T2>
void  test_det (const Matrix<T2> X, const Matrix<T2> Y) {
    Matrix prototype_A = X;
    Matrix prototype_B = Y;
    try {
        std::cout << "Determinant test";
        Proverka(prototype_A.determinant() == 1.00);
        Matrix<T2> prov = prototype_B.determinant() == 1.00;
    }
    catch (Matrix_Exception<int> error) {
        error.set_mistake(2);
    }
}

template<class T2>
void  test_inv (const Matrix<T2> X, const Matrix<T2> Y){
    Matrix prototype_A = X;
    Matrix prototype_B = Y;
    prototype_A.getline() [5] = 55.00;
    prototype_B.getline() [5] = -55.00;
    std::cout << "Inverce test ";
    try{
        Proverka( prototype_A.inverce() == prototype_B );
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(4);

    }
}

template<class T2>
void  test_pow (const Matrix<T2> A, const Matrix<T2> B) {
    try {
        std::cout << "Pow test";
        Matrix X= A;
        Matrix Y= B;
        Matrix prototype_A = X.indentity() ;
        Matrix prototype_B = Y.indentity();

        Proverka(prototype_A.pow(prototype_A, 2) == ( (prototype_A )* 4.00));
    }
    catch (Matrix_Exception<int> error){
        error.set_mistake(2);
    }
}

template<class T2>
void Matrix<T2>::output (){
    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){

            std::cout << massive[row][col] << "  ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}


int main() {
    Matrix A = Matrix<double>(5, 5);
    double k= 1.00;
    for (unsigned int row = 0; row < A.getrow() * A.getcol(); row++) {
        A.getline()[row] = k;
        k = k + 1.00;

    }
    Matrix B = Matrix<double>(5, 5);
    k= 0.00;
    for (unsigned int row = 0; row < B.getrow() * B.getrow(); row++) {
        B.getline()[row] = k;
        k = k + 1.00;
        B.getline()[8] = 21.30;
        B.getline()[5] = 3.00;
        B.getline()[6] = 12.00;
        B.getline()[20] = 1.00;
        B.getline()[16] = 77.00;
        B.getline()[12] = 43.00;
    }



   test_add (A, B);
   test_sub (A, B);
   test_mult (A, B);
   test_exp (A, B);
   test_det(A, B);
   test_inv (A, B);
   test_pow(A, B);
/*
    std::cout << "Matrix A =\n";
    A.output();
    std::cout << "Matrix B =\n";
    B.output();


    std::cout << "Matrix A + B =\n";
    A.addition(B).output();


    std::cout << "Matrix A - B =\n";
    A.subtraction(B).output();

    std::cout << "Matrix A * 5 =\n";
    A.multiplication(5).output();

    std::cout << "Determinant A =" << A.determinant() << " \n";
    std::cout << "Determinant B =" << B.determinant() << " \n";


    std::cout << "Matrix A * B =\n";
    A.multiplication(B).output();

    std::cout << "Matrix A ^ 3 =\n";

    A.pow(A, 3).output();

    std::cout << "Matrix B ^ -1 =\n";
    B.inverce().output();

   // std::cout << "Matrix A ^ -1 =\n";
  // A.inverce().output();
*/
    return 0;
}
