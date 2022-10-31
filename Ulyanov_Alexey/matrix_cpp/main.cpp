#include <iostream>
#include <algorithm>


const unsigned int Max_range = 51;


class Matrix {


public:

    unsigned int rows;
    unsigned int cols;

    double *data;


    Matrix();
    Matrix(const unsigned int row, const unsigned int col);
    Matrix(const Matrix &x);
    ~Matrix();
    Matrix& operator=(const Matrix &x);

    void zero();
    void one();
    void tran();

    void fill_random();
    void fill_certain(const unsigned int len, const double* arrey);
    void output(bool f = false);

};


Matrix::Matrix() {
    std::cout << "Konstruktor 1\n";
    rows = 0;
    cols = 0;

    //data = new double[rows * cols];

}


Matrix::Matrix(const unsigned int row, const unsigned int col) {
    std::cout << "Konstruktor 2\n";
    rows = row;
    cols = col;

    data = new double[row * col];
}


Matrix::~Matrix() {
    std::cout << "Destructor\n";
    delete[] data;
}


Matrix::Matrix(const Matrix &x) {
    std::cout << "Copy now\n";

    rows = x.rows;
    cols = x.cols;

    //delete[] data;
    data = new double[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }
    //data = x.data;
}


Matrix& Matrix::operator=(const Matrix &x) {
    std::cout << "attraction\n";

    rows = x.rows;
    cols = x.cols;

    if (!data) // проверка data на пустоту
        delete[] data;
    data = new double[rows * cols];

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = x.data[idx];
    }

}


void Matrix::zero(){
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = 0.0;
    }
}


void Matrix::one(){
    this->zero();
    for (unsigned int idx = 0; idx < rows; idx++){
        data[idx + rows * idx] = 1.0;
    }
}


void Matrix::tran(){
    unsigned int row = cols;
    unsigned int col = rows;

    double* temp_arrey = new double [rows * cols];
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        temp_arrey[idx] = data[idx];
    }

    for (unsigned int row_idx = 0; row_idx < rows; row_idx++){
        for (unsigned int col_idx = 0; col_idx < cols; col_idx++){
            data[col_idx * rows + row_idx] = temp_arrey[row_idx * cols + col_idx];
        }
    }

    rows = row;
    cols = col;

}





void Matrix::fill_random() {
    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = rand() % Max_range;
    }
}


void Matrix::fill_certain(const unsigned int len, const double* arrey) {
    if (len != rows * cols) return;

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        data[idx] = arrey[idx];
    }
}


void Matrix::output(bool f){
    if (f) std::cout << rows << " " << cols << "\n";

    for (unsigned int idx = 0; idx < rows * cols; idx++){
        std::cout << data[idx] << "  ";
    }
    std::cout << "\n";

    for (unsigned int row = 0; row < rows; row++){
        for (unsigned int col = 0; col < cols; col++){
            std::cout << this->data[row * cols + col] << "  ";
        }
        std::cout << "\n";
    }
}



int main() {

    Matrix B;
    B.output(true);

    Matrix A = Matrix(4, 5);
    //A.output(true);

    B = A;
    A.zero();
    A.one();
    A.fill_random();
    double arrey[20] = {1, 2, 3, 4, 5,
                        6, 7, 8, 9, 10,
                        9, 8, 7, 6, 5,
                        4, 3, 2, 1, 0};
    A.fill_certain(20, arrey);
    A.output(true);
    A.tran();
    B.output();
    A.output(true);

    return 0;
}