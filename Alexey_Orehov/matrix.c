#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Matrix{
    unsigned int rows;
    unsigned int cols;
    double* values;
};

bool same_size(struct Matrix m1, struct Matrix m2){ return (m1.cols == m2.cols && m1.rows == m2.rows);}

struct Matrix m_add(struct Matrix m1, struct Matrix m2){
    if (!same_size(m1, m2)){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    struct Matrix ans = {m1.rows, m1.cols};
    ans.values = (double*) malloc(sizeof(double) * ans.cols * ans.rows);
    for (int index = 0; index < ans.rows * ans.cols; index++){
        ans.values[index] = m1.values[index] + m2.values[index];
    }
    return ans;
}

struct Matrix m_subs(struct Matrix m1, struct Matrix m2){
    if (!same_size(m1, m2)){
        fprintf(stderr, "Matrices should have same size");
        exit(1);
    }
    struct Matrix ans = {m1.rows, m1.cols};
    ans.values = (double*) malloc(sizeof(double) * ans.cols * ans.rows);
    for (int index = 0; index < ans.rows * ans.cols; index++){
        ans.values[index] = m1.values[index] - m2.values[index];
    }
    return ans;
}

struct Matrix m_mult(struct Matrix m1, struct Matrix m2){
    if (m1.rows != m2.cols){
        fprintf(stderr, "number of rows of first matrix should equal to number of cols of second matrix");
        exit(1);
    }
    struct Matrix ans = {m1.rows, m1.cols};
    ans.values = (double*) malloc(sizeof(double) * ans.cols * ans.rows);
    for (int index1 = 0; index1 < ans.rows; index1++){
        for (int index2 = 0; index2 < ans.cols; index2++){
            double summa = 0.f;
            for (int k = 0; k < ans.rows; k++){
                summa += m1.values[index1 * ans.cols + k] * m2.values[k * ans.cols + index2];
            }
            ans.values[ans.cols * index1 + index2] = summa;
        }
    }
    return ans;
}

void printm(struct Matrix matrix){
    for (int row = 0; row < matrix.rows; row++){
        for (int col = 0; col < matrix.cols; col++){
            printf(" %f", matrix.values[row * matrix.cols + col]);
        }
        printf("\n");
    }
}


int main(){
    double values1[6] = {3, 2, 1,
                         0, 1, 2};
    double values2[6] = {1, 2 ,
                         2, 0,
                         3, 1};
    struct Matrix matrix1 = {2, 3, values1};
    struct Matrix matrix2 = {3, 2, values2};

    //printm(m_add(matrix1, matrix2));
    //printm(m_subs(matrix1, matrix2));
    printm(m_mult(matrix1, matrix2));

}