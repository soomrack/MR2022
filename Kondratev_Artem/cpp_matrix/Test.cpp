//
// Created by user on 08.11.22.
//

#include "Test.h"
void test() {
    Matrix res_matrix(2, 2, 0.0);

    double array1[] = {2, 8, 1, 3};
    Matrix matrix1(2,2, array1);

    double array2[] = {4, 9, 21, 13};
    Matrix matrix2(2,2, array2);

    //  = overload test
    res_matrix = matrix1;
    double eq_true_array[] = {2, 8, 1, 3};
    calculation_check(eq_true_array, res_matrix, "= overload");

    //  addition test (matrix)
    res_matrix = matrix1 + matrix2;
    double sum_true_array[] = {6, 17, 22, 16};
    calculation_check(sum_true_array, res_matrix, "addition (matrix)");

    //  addition test (number)
    res_matrix = matrix1 + 2;
    double snum_true_array[] = {4, 10, 3, 5};
    calculation_check(snum_true_array, res_matrix, "addition (number)");

    //  subtraction test
    res_matrix = matrix1 - matrix2;
    double sub_true_array[] = {-2, -1, -20, -10};
    calculation_check(sub_true_array, res_matrix, "subtraction");

    //  multiplication test
    res_matrix = matrix1 * matrix2;
    double multi_true_array[] = {176, 122, 67, 48};
    calculation_check(multi_true_array, res_matrix, "multiplication (matrix)");

    //  multiplication test (number)
    res_matrix = matrix1 * 2;
    double mnum_true_array[] = {4, 16, 2, 6};
    calculation_check(mnum_true_array, res_matrix, "multiplication (number)");

    //  determinant test
    double determinant_true_array[] = {-2};

    double determinant = matrix1.determinant();
    Matrix det_matrix(1, 1, determinant);
    calculation_check(determinant_true_array, det_matrix, "determinant");

    //  transposition test
    double transp_true_array[] = {2, 1, 8, 3};
    res_matrix = matrix1.transposition();
    calculation_check(transp_true_array, res_matrix, "transposition");

    //  inversion test
    double inv_true_array[] = {-1.5, 4, 0.5, -1};
    res_matrix = matrix1.inversion();
    calculation_check(inv_true_array, res_matrix, "inversion");

    //  inverse multiplication test
    double inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
    res_matrix = matrix1 / matrix2;
    calculation_check(inv_multi_true_array, res_matrix, "inverse multiplication");

    //  power 0 test
    double pow0_true_array[] = {1, 0, 0, 1};
    res_matrix = matrix1.power(0);
    calculation_check(pow0_true_array, res_matrix, "power 0");

    //  power 3 test
    double pow3_true_array[] = {64, 216, 27, 91};
    res_matrix = matrix1.power(3);
    calculation_check(pow3_true_array, res_matrix, "power 3");

    //  power -4 test
    double pow4_true_array[] = {30.5625, -72.5, -9.0625, 21.5};
    res_matrix = matrix1.power(-4);
    calculation_check(pow4_true_array, res_matrix, "power -4");

    //  exp test
    double array3[] = {2, 2, 2, 2};
    Matrix matrix3(2, 2, array3);
    double exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
    res_matrix = Matrix::exp(matrix3);
    calculation_check(exp_true_array, res_matrix, "Matrix exp");
}