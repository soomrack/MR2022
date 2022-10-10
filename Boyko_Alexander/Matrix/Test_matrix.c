#include "matrix.h"


int main() {
    struct Matrix Mat_A = create_zero_matrix(4,3);
    struct Matrix res_C;
    fill_matrix_summ(&Mat_A);
    print_matx(Mat_A);
    struct Matrix Mat_B = create_zero_matrix(2, 3);
    fill_matrix_mult(&Mat_B);

    print_matx(Mat_B);
    res_C = matrix_mult(&Mat_A,&Mat_B);
    print_matx(res_C);
    print_matx(ZERO);
    free(res_C.values);
    return 0;
}
