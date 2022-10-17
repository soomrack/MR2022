#include <windows.h>
#include "matrix_lib.h"

#define TEST_PASSED 2
#define TEST_FAILED 4
#define DEFAULT 7

HANDLE  hConsole;


void test_add(){
    double data1[6] = {1, 2, 3,
                       4, 5, 6};
    double data2[6] = {8, -1, 1,
                       -2, 2, 4};
    double ans_d[6] = {9, 1, 4,
                       2, 7, 10};
    Matrix matrix1 = {2, 3, data1};
    Matrix matrix2 = {2, 3, data2};
    Matrix ans = {2, 3, ans_d};
    if (is_equal(add(copy(matrix1), matrix2), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Addition test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Addition test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_sub(){
    double data1[6] = {1, 2, 3,
                       4, 5, 6};
    double data2[6] = {8, -1, 1,
                       -2, 2, 4};
    double ans_d[6] = {-7, 3, 2,
                       6, 3, 2};
    Matrix matrix1 = {2, 3, data1};
    Matrix matrix2 = {2, 3, data2};
    Matrix ans = {2, 3, ans_d};
    if (is_equal(sub(copy(matrix1), matrix2), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Subtraction test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Subtraction test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_mul(){
    double data1[6] = {1, 2, 3,
                       4, 5, 6};
    double data2[9] = {8, -1, 1,
                       -2, 2, 4,
                       7, 3, 0};
    double ans_data[6] = {25, 12, 9,
                          64, 24, 24};
    Matrix matrix1 = {2, 3, data1};
    Matrix matrix2 = {3, 3, data2};
    Matrix ans = {2, 3, ans_data};
    if (is_equal(mul(copy(matrix1), matrix2), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Multiplication test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Multiplication test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_s_mul(){
    double data1[9] = {1, 2, 3,
                       4, 5, 6,
                       7, 8, 9};
    double scalar = 3.2;
    double ans_data[9] = {3.2, 6.4,9.6,
                          12.8, 16.0,19.2,
                          22.4, 25.6, 28.8};
    Matrix matrix = {3, 3, data1};
    Matrix ans = {3, 3, ans_data};
    if (is_equal(s_mul(matrix, scalar), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Scalar multiplication test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Scalar multiplication test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}

void test_det(){
    double data[9] = {1, -2, 3,
                       0, 7, 4,
                       5, 3, -3};
    double ans = -178.0;
    Matrix matrix = {3, 3, data};
    if (m_det(matrix) == ans){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Determinant test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Determinant test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_trans(){
    double data[9] = {1, -2, 3,
                      0, 7, 4,
                      5, 3, -3};
    double ans_d[9] = {1, 0, 5,
                       -2, 7, 3,
                       3, 4, -3};
    Matrix matrix = {3, 3, data};
    Matrix ans = {3, 3, ans_d};
    if (is_equal(transpose(copy(matrix)), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Transposition test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Transposition test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_inv(){
    double data[9] = {1, -2, 1,
                      2, 1, -1,
                      3, 2, -2};
    double ans_data[9] = {0, 2, -1,
                          -1, 5, -3,
                          -1, 8, -5};
    Matrix matrix = {3, 3, data};
    Matrix ans = {3, 3, ans_data};
    if (is_equal(m_inv(copy(matrix)), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Matrix inversion test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Matrix inversion test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_inv_mul(){
    int size = 20;
    Matrix mat = create_random(size, size, 5);
    if (is_equal(mul(copy(mat), m_inv(copy(mat))), create_identity(size))){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Inverse matrix multiplication test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Inverse matrix multiplication hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_triangle(){
    double data[16] = {-1, 2, 1, 2,
                       -1, 3, 2, 4,
                       -3, 5, 4, 8,
                       -2, 3, 2, 3};
    double ans_data[16] = {-1, 2, 1, 2,
                           0, 1, 1, 2,
                           0, 0, 2, 4,
                           0, 0, 0, -1};
    Matrix mat = {4, 4, data};
    Matrix ans = {4, 4, ans_data};
    if (is_equal(upper_triangle(mat), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("upper triangle matrix transformation test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("upper triangle matrix transformation hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    test_add();
    test_sub();
    test_mul();
    test_s_mul();
    test_triangle();
    test_det();
    test_trans();
    test_inv();
    test_inv_mul();
}


int main(){
    test();
    return 0;
}