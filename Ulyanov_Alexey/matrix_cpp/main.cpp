#include <iostream>
#include <algorithm>

const unsigned int Max_range = 51;


class Matrix {
public:

    unsigned int rows;
    unsigned int cols;

    double **value;


    Matrix(const int row = 0, const int col = 0){

        this->rows = std::max(row, 0);
        this->cols = std::max(col, 0);

        value = reinterpret_cast<double **>(new double[this->rows]);
        for (unsigned int idx = 0; idx < this->rows; idx++){
            value[idx] = new double[this->cols];
        }
    }


    ~Matrix(){
        for (unsigned int idx = 0; idx < this->rows; idx++){
            delete []value[idx];
        }
        delete []value;
    }


    void zero(){
        for (unsigned int row = 0; row < rows; row++){
            for (unsigned int col = 0; col < cols; col++){
                this->value[row][col] = 0.0;
            }
        }
    }


    void one(){
        this->zero();
        for (unsigned int idx = 0; idx < std::min(this->rows, this->cols); idx++){
            this->value[idx][idx] = 1.0;
        }
    }


    void tran(){

        Matrix temp = Matrix(this->cols, this->rows);
        for (unsigned int row = 0; row < temp.rows; row++){
            for (unsigned int col = 0; col < temp.cols; col++){
                temp.value[row][col] = this->value[col][row];
            }
        }

        this->~Matrix();
        this->value = reinterpret_cast<double **>(new double[temp.rows]);
        for (unsigned int idx = 0; idx < temp.rows; idx++){
            this->value[idx] = new double[temp.cols];
        }

        this->rows = temp.rows;
        this->cols = temp.cols;
        for (unsigned int row = 0; row < this->rows; row++){
            for (unsigned int col = 0; col < this->cols; col++){
                this->value[row][col] = temp.value[row][col];
            }
        }

        temp.~Matrix();

    }


    void fill_random(){
        for (unsigned int row = 0; row < this->rows; row++){
            for (unsigned int col = 0; col < this->cols; col++){
                this->value[row][col] = rand() % Max_range;
            }
        }
    }


    void output(bool f = false){
        if (f) std::cout << this->rows << " " << this->cols << std::endl;
        for (unsigned int row = 0; row < rows; row++){
            for (unsigned int col = 0; col < cols; col++){
                std::cout << this->value[row][col] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

};




int main() {

    Matrix A = Matrix(4, 5);
    A.fill_random();
    A.output();

    Matrix B = Matrix(3, 4);
    B.one();
    B.output(true);
    B.tran();
    B.output(true);

    return 0;
}
