#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

#define MAX_RANGE 26

struct Mat {
    unsigned int cols;
    unsigned int rows;

    double **values;
};

struct Mat creation (unsigned int rows, unsigned int cols) {
    struct Mat rez;
    rez.rows = rows;
    rez.cols = cols;

    double **array = (double **) malloc(rows * sizeof(double *));  // Выделили память для адресного массива
    for(int row = 0; row < rows; row++){
        array[row] = (double  *) malloc(cols * sizeof(double *));  // Выделяем память для каждой строчки (т.к. мы не указываем номер элемента в строке (второе значение), то массив становится адресом обрабатываемой строчки)
    }
    rez.values = array;
    return rez;
}

struct Mat Empty() {
    struct Mat rez = creation(0, 0);
    return rez;
}

struct Mat zero(unsigned int rows, unsigned int cols){
    struct Mat rez = creation(rows, cols);
    for(int row = 0; row < rows; row++){
        for(int col = 0; col < rows; col++){
            rez.values[row][col] = 0.0;
        }
    }
    return rez;
}

struct Mat Unit(unsigned int n){
    struct Mat rez = zero(n, n);
    for(int i = 0; i < n; i++){
        rez.values[i][i] = 1.0;
    }
    return rez;
}

struct Mat transponation(struct Mat x){
    struct Mat rez = creation(x.rows, x.cols);
    for(int col = 0; col < x.cols; col++){
        for(int row = 0; row < x.rows; row++){
            rez.values[col][row] = x.values[row][col];
        }
    }
    return rez;
}

struct Mat minor(int row_to_cut, int col_to_cut, struct Mat x){
    struct Mat rez = creation(x.rows - 1, x.cols - 1);

    for(int row = 0; row < row_to_cut; row++){
        for(int col = 0; col < col_to_cut; col++){
            rez.values[row][col] = x.values[row][col];
        }
    }

    for(int row = row_to_cut; row < x.rows; row++){
        for(int col = 0; col < col_to_cut; col++){
            rez.values[row][col] = x.values[row+1][col];
        }
    }

    for(int row = 0; row < row_to_cut; row++){
        for(int col = col_to_cut; col < x.cols; col++){
            rez.values[row][col] = x.values[row][col+1];
        }
    }

    for(int row = row_to_cut; row < x.rows; row++){
        for(int col = col_to_cut; col < x.cols; col++){
            rez.values[row][col] = x.values[row+1][col+1];
        }
    }
    return rez;
}

struct Mat addition(struct Mat x, struct Mat y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return Empty();

    struct Mat rez = creation(x.rows, x.cols);
    for(int row = 0; row < x.rows; row++){
        for(int col = 0; col < x.cols; col++){
            rez.values[row][col] = x.values[row][col] + y.values[row][col];
        }
    }
    return rez;
}

struct Mat substraction(struct Mat x, struct Mat y){
    if ((x.cols != y.cols) || (x.rows != y.rows)) return Empty();

    struct Mat rez = creation(x.rows, x.cols);
    for(int row = 0; row < x.rows; row++){
        for(int col = 0; col < x.cols; col++){
            rez.values[row][col] = x.values[row][col] - y.values[row][col];
        }
    }
    return rez;
}

struct Mat multiplicaion(struct Mat x, struct Mat y){
    if (x.cols != y.rows) return Empty();

    struct Mat rez = creation(x.rows, y.cols);
    for(int row = 0; row < x.rows; row++){
        for(int col = 0; col < y.cols; col++){
            rez.values[row][col] = 0.0;
            for(int k = 0; k < x.cols; k++){
                rez.values[row][col] += x.values[row][k] * y.values[k][col];
            }
        }
    }
    return rez;
}

struct Mat multiplication_k(struct Mat x, double k){
    struct Mat rez = creation(x.rows, x.cols);
    for(int row = 0; row < x.rows; row++){
        for(int col = 0; col < x.cols; col++){
            rez.values[row][col] = x.values[row][col] * k;
        }
    }
    return rez;
}

double det(struct Mat x){
    if (x.cols != x.rows) return 0.0;

    if (x.cols == 1)return x.values[0][0];

    else{
        double rez = 0.0;
        for(int col = 0; col < x.cols; col++){
            struct Mat temp = minor(0, col, x);
            rez += pow(-1, col) * x.values[0][col] * det(temp);
            free(temp.values);
        }
        return rez;
    }
}

struct Mat reverse(struct Mat x){
    double deter = det(x);
    if ((x.rows != x.cols) || (deter == 0)) return Empty();

    struct Mat rez = creation(x.rows, x.cols);
    for(int row = 0; row < x.rows; row++){
        for(int col = 0; col < x.cols; col++){
            struct Mat temp = minor(row, col, x);
            rez.values[row][col] = pow(-1, row + col) * det(temp);
            free(temp.values);
        }
    }
    return multiplication_k(rez, 1/deter);
}

struct Mat pow_m(struct Mat x, unsigned int n){
    if (x.rows != x.cols) return Empty();

    if (n == 0) return Unit(x.rows);

    struct Mat rez = creation(x.rows, x.cols);
    rez.values = x.values;
    for(int i = 1; i < n; i++){
        rez = multiplicaion(rez, x);
    }
    return rez;
}

void output(struct Mat out) {
    for(int row = 0; row < out.rows; row++){
        for(int col = 0; col < out.cols; col++){
            printf("%.2lf  ", out.values[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    struct Mat A = creation(4, 4);
    struct Mat B = creation(4, 4);

    for(int i = 0; i < A.rows; i++){
        for(int j = 0; j < A.cols; j++){
            A.values[i][j] = rand() % MAX_RANGE;
        }
    }

    for(int i = 0; i < B.rows; i++){
        for(int j = 0; j < B.cols; j++){
            B.values[i][j] = rand() % MAX_RANGE;
        }
    }
    output(A);
    output(B);
}
