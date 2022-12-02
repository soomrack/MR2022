#include "matrix.c"

double ADD_VAL[9] = {0.0,1.0, 2.0,
                     1.0,3.0,5.0,
                     2.0,5.0,8.0};
Matrix MAT_ADD = {3, 3, ADD_VAL};

double SUB_VAL[9] = {0.0,1.0, 2.0,
                     1.0,1.0,1.0,
                     2.0,1.0,0.0};
Matrix MAT_SUB = {3, 3, SUB_VAL};

double MUL_VAL[9] = {0.0,14.0, 28.0,
                     0.0,20.0,40.0,
                     0.0,26.0,52.0};
Matrix MAT_MUL = {3, 3, MUL_VAL};

double MAT_VAL[9] = {0.0,2.0, 2.0,
                     1.0,5.0,3.0,
                     2.0,3.0,4.0};
Matrix MAT_DET = {3, 3, MAT_VAL};

double DET_VAL = -10;

double EXP_VAL[9] = {91.183965,160.707182,231.230400,
                     160.707182,286.340779,409.974376,
                     231.230400,409.974376,589.718351};
Matrix MAT_EXP = {3,3,EXP_VAL};

double EQUAL_ACCURACY = 0.001;

int is_mat_equal(const Matrix A, const Matrix B){
    if(A.cols != B.cols){
        return 0;
    }
    if(A.rows != B.rows){
        return 0;
    }
    for(int k = 0; k < A.cols * A.rows; k++){
        if (fabs(A.values[k] - B.values[k]) > EQUAL_ACCURACY) {
            return 0;
        }
    }
    return 1;
}

void check_add(){
    Matrix A = create_zero_matrix(3,3);
    Matrix res;
    fill_matrix_summ(&A);
    Matrix B = create_zero_matrix(3, 3);
    fill_matrix_mult(&B);

    res = matrix_add(A,B);
    if (!is_mat_equal(res,MAT_ADD)){
        printf("ERROR: ADDITION INCORRECT\n");
        free_mat(&A);
        free_mat(&B);
        free_mat(&res);
        return;
    }
    free_mat(&A);
    free_mat(&B);
    free_mat(&res);
    printf("ADDITION CORRECT\n");
}

void check_sub(){
    Matrix A = create_zero_matrix(3,3);
    Matrix res;
    fill_matrix_summ(&A);
    Matrix B = create_zero_matrix(3, 3);
    fill_matrix_mult(&B);

    res = matrix_subt(A,B);
    if (!is_mat_equal(res,MAT_SUB)){
        printf("ERROR: SUBTRACTION INCORRECT\n");
        free_mat(&A);
        free_mat(&B);
        free_mat(&res);
        return;
    }
    free_mat(&A);
    free_mat(&B);
    free_mat(&res);
    printf("SUBTRACTION CORRECT\n");
}

void check_mult(){
    Matrix A = create_zero_matrix(3,4);
    Matrix res;
    fill_matrix_summ(&A);
    Matrix B = create_zero_matrix(4, 3);
    fill_matrix_mult(&B);

    res = matrix_mult(A,B);
    if (!is_mat_equal(res,MAT_MUL)){
        printf("ERROR: MULTIPLICATION INCORRECT\n");
        free_mat(&A);
        free_mat(&B);
        free_mat(&res);
        return;
    }
    free_mat(&A);
    free_mat(&B);
    free_mat(&res);
    printf("MULTIPLICATION CORRECT\n");
}

void check_det(){
    Matrix A = copy_mat(MAT_DET);
    double det_a = matrix_det(A);
    if (det_a != DET_VAL){
        printf("ERROR: DETERMINANT INCORRECT\n");
        free_mat(&A);
        return;
    }
    free_mat(&A);
    printf("DETERMINANT CORRECT\n");
}

void check_exp(){
    Matrix A = create_zero_matrix(3,3);
    fill_matrix_summ(&A);
    Matrix res = matrix_exp(A);
    if (!is_mat_equal(res,MAT_EXP)){
        printf("ERROR: EXPONENT INCORRECT\n");
        free_mat(&A);
        free_mat(&res);
        return;
    }
    free_mat(&A);
    free_mat(&res);
    printf("EXPONENT CORRECT\n");
}

int main() {
    for(int k = 0; k < 100; k++){
        check_add();

        check_sub();

        check_mult();

        check_det();

        check_exp();

    }

    return 0;
}
