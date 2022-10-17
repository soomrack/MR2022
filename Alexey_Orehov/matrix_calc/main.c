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
    if (equal(add(copy(matrix1), matrix2), ans)){
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
    if (equal(sub(copy(matrix1), matrix2), ans)){
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
    if (equal(mul(copy(matrix1), matrix2), ans)){
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
    if (equal( s_mul(matrix, scalar), ans)){
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
    if (equal(transpose(copy(matrix)), ans)){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Transposition test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Transposition test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void inv_mul_test(){
    int size = 4;
    Matrix mat = create_random(size, size, 5);
    printm(mat);
    printm(mul(copy(mat), m_inv(copy(mat))));
    if (equal( mul(copy(mat), m_inv(mat)), create_identity(size))){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Inverse matrix multiplication test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Inverse matrix multiplication hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


int main(){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    test_add();
    test_sub();
    test_mul();
    test_s_mul();
    test_det();
    test_trans();
    return 0;
}