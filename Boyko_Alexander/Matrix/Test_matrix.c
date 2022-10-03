
#include "matrix.h"


int main() {
    struct Matrix Mat_A;
    struct Matrix Mat_B;
    struct Matrix res_C;
    create_zero_matrix(&Mat_A,4,3, "Mat_A");
    create_zero_matrix(&Mat_B, 3, 4, "Mat_B");
    fill_matrix_summ(&Mat_A);
    fill_matrix_mult(&Mat_B);
    print_matx(Mat_A);
    print_matx(Mat_B);
    res_C = matrix_mult(&Mat_A,&Mat_B);
    print_matx(res_C);
    free(res_C.values);
    return 0;
}
