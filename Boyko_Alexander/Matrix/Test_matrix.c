
#include "matrix.h"


int main() {
    struct Matrix Mat_A;
    struct Matrix Mat_B;
    struct Matrix res_C;
    create_empty_matrix(&Mat_A,3,3, "Mat_A");
    create_empty_matrix(&Mat_B, 3, 3, "Mat_B");
    fill_matrix_summ(&Mat_A);
    fill_matrix_mult(&Mat_B);
    res_C = matrix_subt(&Mat_B,&Mat_A);
    print_matx(Mat_A);
    print_matx(Mat_B);
    print_matx(res_C);
    return 0;
}
