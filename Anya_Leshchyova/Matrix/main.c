#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <minmax.h>

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <minmax.h>


double DELTA=0.000001;


typedef struct {
    unsigned int rowS;
    unsigned int colS;
    double *line;
    double **massive;
} Matrix;


typedef enum {
    Matrix_sizes_are_different,
    Determinant_is_zero,
    Matrix_data_cannot_be_multiplied,
    The_matrix_is_not_square,
} ERROR;


void free_matrix (Matrix A){
    free(A.line);
    free(A.massive);
}


Matrix memory_matrix (const unsigned int rows, const unsigned int cols){
    Matrix result;
    result.rowS = rows;
    result.colS = cols;
    result.line = (double*)malloc(rows * cols * sizeof (double *));
    result.massive = (double**)malloc(rows * sizeof(double *));
    for(unsigned int i = 0; i < rows; i ++){
        result.massive[i] = result.line + i * cols;
    }
    return result;
}


void mistake (ERROR kod_mistake){
    switch (kod_mistake){
        case Matrix_sizes_are_different:
            printf("Matrix sizes are different\n");
            break;
        case Determinant_is_zero:
            printf("Determinant is zero\n");
            break;
        case Matrix_data_cannot_be_multiplied:
            printf("Matrix data cannot be multiplied\n");
            break;
        case The_matrix_is_not_square:
            printf("The matrix is not square\n");
            break;
        default:
            printf("Another error\n");
    }
}


Matrix empty_matrix(){
    Matrix empty = {0, 0, NULL, NULL};
    return empty;
}


Matrix zero_matrix(unsigned int rows,unsigned int cols ){
    Matrix result =memory_matrix (rows, cols);
    for(unsigned int number = 0; number < rows * cols; number++) {
        result.line[number] = 0.00;
    }
    return result;
}


Matrix identity_matrix(unsigned int rows,unsigned int cols ){
    Matrix result = zero_matrix (rows, cols);
    for(unsigned int number = 0; number < min(result.rowS, result.colS); number++) {
        result.massive[number][number] = 1.00;
    }
    return result;
}


int are_the_matrices_equal(Matrix A, Matrix B) {
    if(A.rowS != B.rowS || A.colS != B.colS) return 0;
    for(unsigned int number = 0; number <= A.rowS * A.colS; number++) {
        if(fabs(A.massive[number] - B.massive[number]) > DELTA)return 1;
    }
}

Matrix copy_matrix( const Matrix A ){
    Matrix copy = memory_matrix(A.rowS, A.colS);
    for(unsigned int number = 0; number <= A.rowS * A.colS; number++) {
        copy.line[number] = A.line[number] ;
    }
    return copy;
}


//работает только с матрицами 3 на 3
Matrix change_matrix( double A[3][3]) {
    Matrix result = memory_matrix(3,3);
    for(int i_row = 0; i_row < 3; i_row++) {
        for(int j_col = 0; j_col < 3; j_col++) {
            result.massive[i_row][j_col] = A[i_row][j_col];
        }
    }
    return result;
}


Matrix addition_matrix(const Matrix A,const Matrix B){
    if( ! (A.rowS == B.rowS & A.colS == B.colS) ) {
        mistake( (Matrix_sizes_are_different));
        return empty_matrix();
    }
    Matrix sum = memory_matrix(A.rowS, A.colS);
    for(unsigned int number = 0; number < sum.rowS * sum.colS; number++) {
            sum.line[number] = A.line[number] + B.line[number];
        }
    return sum;
}


Matrix subtraction_matrix(const Matrix A,const Matrix B){
    if( ! (A.rowS == B.rowS & A.colS == B.colS) ) {
        mistake( (Matrix_sizes_are_different));
        return empty_matrix();
    }
    Matrix mun = memory_matrix(A.rowS, A.colS);
    for(unsigned int number = 0; number < mun.rowS * mun.colS; number++) {
        mun.line[number] = A.line[number] - B.line[number];
    }
    return mun;
}


Matrix multiplication_matrix(const Matrix A,const Matrix B) {
    if(A.rowS != B.colS) {
        mistake(Matrix_data_cannot_be_multiplied);
        return empty_matrix();
    }
    Matrix ymn = memory_matrix(A.rowS, A.colS);;
    for(unsigned int i_row = 0; i_row < ymn.rowS; i_row++) {
        for(unsigned int j_col = 0; j_col < ymn.colS; j_col++) {
            ymn.massive[i_row][j_col] = 0;
            for( unsigned int h = 0; h < A.colS; h++) {
                ymn.massive[i_row][j_col] += A.massive[i_row][h] * B.massive[h][j_col];
            }
        }
    }
    return ymn;
}


Matrix minor_matrix (const Matrix A, unsigned int  x, unsigned int y)  {
    Matrix det_min= memory_matrix (A.rowS-1, A.colS-1);
    unsigned int auxiliary_1 = 0, auxiliary_2 = 0;
    for(unsigned int i_row = 0; i_row < A.rowS; i_row++) {
        if(i_row == x) {
            auxiliary_1 = i_row;
            continue;
        }
        for(unsigned int j_col = 0; j_col < A.colS; j_col++) {
            if (j_col == y){
                auxiliary_2 = j_col;
                continue;
            }
            det_min.massive[auxiliary_1][auxiliary_2] = A.massive[i_row][j_col];
            auxiliary_2 += 1;
        }
        auxiliary_2 = 0;
        auxiliary_1 += 1;
    }
    return det_min;
}


double determinant_matrix (const Matrix A){
    double znak = 1.00;
    if(A.colS != A.rowS) {
        mistake( The_matrix_is_not_square);
        return 0.00;
    }
    if(A.colS == 1){
        return A.massive[0][0];
    }
    if( A.colS == 2){
        return A.massive[0][0] * A.massive[1][1] - A.massive[1][0] * A.massive[0][1];
    }
    double det = 0.00;
    for(unsigned int i = 0; i < A.colS; i++){
        Matrix minor_auxiliary = minor_matrix (A,0,i);
        det = det + znak * A.massive[0][i] * determinant_matrix(minor_auxiliary);
        znak *= -1.00;
        free_matrix(minor_auxiliary);
    }
    return det;
}


Matrix multiplication_k_matrix(const Matrix A, double factor) {
    Matrix result = memory_matrix(A.rowS, A.colS);
    for(unsigned int number = 0; number < result .rowS * result .colS; number++) {
        result.line[number] = A.line[number] * factor;
    }
    return result;
}


Matrix transposition_matrix (const Matrix A) {
    Matrix result = memory_matrix(A.rowS, A.colS);;
    for(unsigned int i_row = 0; i_row < result.rowS; i_row++) {
        for(unsigned int j_col = 0; j_col < result.colS; j_col++) {
            result.massive[i_row][j_col] = A.massive[j_col][i_row];
        }
    }
    return result;
}


Matrix inverce_matrix (Matrix A){
    double det_A = determinant_matrix(A);
    double znak = 1.00;
    Matrix result = memory_matrix(A.rowS, A.colS);;
    Matrix result_trans = memory_matrix(A.rowS, A.colS);;
    if(fabs(det_A) < DELTA) {
        mistake(Determinant_is_zero);
        return empty_matrix();
    }
    for(int i = 0; i < A.rowS; i++) {
        for(int j = 0; j < A.colS; j++) {
            Matrix minor_auxiliary = minor_matrix(A, i, j);
            result.massive[i][j] = znak * determinant_matrix(minor_auxiliary) / det_A;
            znak *= -1;
            free_matrix((minor_auxiliary));
        }
    }
    result_trans = transposition_matrix(result);
    return  result_trans;
}


Matrix pow_matrix (const Matrix A, unsigned int n){
    if (n == 0) return identity_matrix(A.rowS,A.colS);
    Matrix result = identity_matrix(A.rowS,A.colS);
    Matrix power = empty_matrix();
    Matrix help2 = empty_matrix();
    for (unsigned  int i = 0; i < n; i++){
        free_matrix(power);
        power = multiplication_matrix(result,A);
        free_matrix(result);
        result = copy_matrix(power);
    }
    return  power;
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


Matrix exponent_matrix( const Matrix A, unsigned int step) {
    if(A.colS != A.rowS) {
        mistake(The_matrix_is_not_square);
        return empty_matrix();
    }
    Matrix result_exp = memory_matrix(A.rowS, A.colS);
    Matrix help_exp = zero_matrix(A.rowS, A.colS);
    free_matrix(result_exp);
    result_exp = copy_matrix (A);
    double factor = 0.5;
    for(int unsigned i = 2; i <= step; i++) {
        free_matrix(help_exp);
        Matrix power = pow_matrix(A, i);
        help_exp =addition_matrix( result_exp, multiplication_k_matrix( power, factor));
        free_matrix(result_exp);
        result_exp = copy_matrix(help_exp) ;
        free_matrix(power);
        factor = 1 / factorial(i+1);
    }
    return addition_matrix(result_exp, identity_matrix( A.rowS, A.colS ));
}


void output_matrix (Matrix A){
    for (unsigned int i_row = 0; i_row < A.rowS; i_row++){
        for (unsigned int j_col = 0; j_col < A.colS; j_col++){
            printf("%f ", A.massive[i_row][j_col]);
        }
        printf("\n");
    }
    printf("\n");
}


void test_matrix (Matrix A, char metod) {
    double addition[3][3] = {{1.00,  3.00,  9.00},
                             {9.00,  11.00, 17.00},
                             {17.00, 19.00, 21.00}};
    double subtraction[3][3] = {{-1.00, -1.00, 3.00},
                                {-1.00, -1.00, 3.00},
                                {-1.00, -1.00, -1.00}};
    double multiplication[3][3] = {{59.00,  66.00,  73.00},
                                   {119.00, 138.00, 157.00},
                                   {143.00, 170.00, 197.00}};
    double inverce[3][3] = {{-2.50, 2.75,  -1.25},
                            {2.50,  -3.00, 1.50},
                            {-0.25, 0.50,  -0.25}};
    double stepen_3[3][3] = {{796.00,  977.00,  1602.00},
                             {1868.00, 2261.00, 3530.00},
                             {2476.00, 2973.00, 4506.00}};
    double exponent[3][3] = {{27.00, 30.50, 41.00},
                             {54.00, 65.5,  97.00},
                             {66.00, 80.50, 130.00}};
    int auxiliary;
    for(int i = 0; i < 1; i++){
        if(metod == '+') {
            Matrix sum = change_matrix(addition);
            auxiliary = are_the_matrices_equal(A, sum);
            break;
        }
        if(metod == '-') {
            Matrix min = change_matrix(subtraction);
            auxiliary = are_the_matrices_equal(A, min);
            break;
        }
        if(metod == '*') {
            Matrix ymn = change_matrix(multiplication);
            auxiliary = are_the_matrices_equal(A, ymn);
            break;
        }
        if(metod == 'r') {
            Matrix inv = change_matrix(inverce);
            auxiliary = are_the_matrices_equal(A, inv);
            break;
        }
        if(metod == '^') {
            Matrix step = change_matrix(stepen_3);
            auxiliary = are_the_matrices_equal(A, step);
            break;
        }
        if(metod == 'e') {
            Matrix exp = change_matrix(exponent);
            auxiliary = are_the_matrices_equal(A, exp);
            break;
        }
        else {
            printf("Unknown check\n");
            printf("\n");
        }

    }
    switch (auxiliary) {
        case 0:
            printf("Made a mistake --> %c\n", metod);
            printf("\n");
            break;
        case 1:
            printf("Operation --> %c <-- performed correctly\n", metod);
            printf("\n");
            break;
        default:
            printf("Error in test program\n", metod);
            printf("\n");
    }
}


int main() {
    /* - Можно задать матрицу с собственными числами
   double AA[3][3] ={{0.00,1.00,6.00},
                           {4.00,5.00,10.00},
                          {8.00,9.00,10.00}};
   double BB[3][3] ={{1.00,2.00,3.00},
                              {5.00,6.00,7.00},
                              {9.00,10.00,11.00}};
   Matrix A=change_matrix(AA);
   Matrix B=change_matrix(BB);
    */

    Matrix A= memory_matrix(3, 3);
    Matrix B = memory_matrix(3, 3);
    double n=-1.00,k=-1.00;
    for(int i = 0; i < A.rowS; i++){
        k=k+1.00;
        for (int j = 0; j < A.colS; j++){
            n=n+1.00;
            A.massive[i][j] = k+n;
            A.massive[1][2] = 10;
            A.massive[0][2] = 6;
        }
    }
    n=-1.00;
    k=-1.00;
    for(int i = 0; i < B.rowS; i++){
        k=k+1.00;
        for(int j = 0; j < B.colS; j++){
            n=n+1.00;
            B.massive[i][j] = k+n+1.00;
        }
    }

    printf("          Matrix A =\n");
    output_matrix(A);

    printf("          Matrix B =\n");
    output_matrix(B);

    printf("          Result A + B =\n");
    output_matrix (addition_matrix (A,B));
    test_matrix(addition_matrix (A,B),'+');

    printf("          Result A - B =\n");
    output_matrix (subtraction_matrix (A,B));
    test_matrix(subtraction_matrix (A,B),'-');

    printf("          Result A * B =\n");
    output_matrix(multiplication_matrix(A,B));
    test_matrix(multiplication_matrix (A,B),'*');

    printf("Determinant A = %f\n", determinant_matrix(A));
    printf("Determinant B = %f\n", determinant_matrix(B));
    printf("\n");

    printf("          Result A * 5 =\n");
    output_matrix (multiplication_k_matrix(A,5));

    printf("          Transpose matrix A =\n");
    output_matrix(transposition_matrix(A));
    printf("          Transpose matrix B =\n");
    output_matrix(transposition_matrix(B));

    printf("          Inverce matrix A =\n");
    output_matrix(inverce_matrix(A));
    test_matrix(inverce_matrix(A),'r');
    printf("          Inverce matrix B =\n");
    output_matrix(inverce_matrix(B));

    printf("          Result A ^ 3 =\n");
    output_matrix(pow_matrix(A,3));
    test_matrix(pow_matrix(A,3),'^');

    printf("          Result exp = \n");
    output_matrix(exponent_matrix(A,2));
    test_matrix(exponent_matrix(A,2),'e');

    return 0;
}