#include <windows.h>
#include "Matrix.h"

#define TEST_PASSED 2
#define TEST_FAILED 4
#define DEFAULT 7

HANDLE  hConsole;


void test_equal(){
    double val1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double val2[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    double val3[9] = {1, 2, 3, 4, 5, 6, 9, 8, 9};
    Matrix mat1 = Matrix(3, 3).fill_from_array(val1);
    Matrix mat2 = Matrix(3, 3).fill_from_array(val2);
    Matrix mat3 = Matrix(3, 3).fill_from_array(val3);
    if (mat1 == mat2 && mat1 != mat3 && mat2 != mat3){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Equal check test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Equal check test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_add(){
    double data1[6] = {1, 2, 3,
                       4, 5, 6};
    double data2[6] = {8, -1, 1,
                       -2, 2, 4};
    double ans_d[6] = {9, 1, 4,
                       2, 7, 10};
    Matrix matrix1 = Matrix(3, 2).fill_from_array(data1);
    Matrix matrix2 = Matrix(3, 2).fill_from_array(data2);
    Matrix ans = Matrix(3, 2).fill_from_array(ans_d);
    if (ans == matrix1 + matrix2){
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
    Matrix matrix1 = Matrix(3, 2).fill_from_array(data1);
    Matrix matrix2 = Matrix(3, 2).fill_from_array(data2);
    Matrix ans = Matrix(3, 2).fill_from_array(ans_d);
    if (matrix1 - matrix2 == ans){
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
    Matrix matrix1 = Matrix(2, 3).fill_from_array(data1);
    Matrix matrix2 = Matrix(3, 3).fill_from_array(data2);
    Matrix ans = Matrix(2, 3).fill_from_array(ans_data);
    if (matrix1 * matrix2 == ans){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Multiplication test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Multiplication test hasn't been passed\n");
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
    Matrix matrix = Matrix(3, 3).fill_from_array(data);
    Matrix ans = Matrix(3, 3).fill_from_array(ans_data);
    if (matrix.inv() == ans){
        SetConsoleTextAttribute(hConsole, TEST_PASSED);
        printf("Inverse matrix test passed\n");
    }
    else{
        SetConsoleTextAttribute(hConsole, TEST_FAILED);
        printf("Inverse matrix test hasn't been passed\n");
    }
    SetConsoleTextAttribute(hConsole, DEFAULT);
}


void test_inv_mul(int num = 100, int size = 5) {
    for (int iteration = 0; iteration < num; iteration++){
        Matrix A = Matrix(size, size).set_random(-10, 10);
        if (!(A * A.inv()).is_identity()) {
            SetConsoleTextAttribute(hConsole, TEST_FAILED);
            printf("Inverse matrix multiplication test hasn't been passed\n");
            return;
        }
    }
    SetConsoleTextAttribute(hConsole, TEST_PASSED);
    printf("Inverse matrix multiplication test passed\n");
    SetConsoleTextAttribute(hConsole, DEFAULT);
}

unsigned long int MatrixMemory::total_memory = 0;


int main(){
//    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    test_equal();
//    test_add();
//    test_sub();
//    test_mul();
//    test_inv();
//    test_inv_mul();
//    double values[9] = {1, 0, 0,
//                        0, 2, 0,
//                        0 ,0, 3};
//    Matrix A = Matrix(3, 3).fill_from_array(values);
//    std::cout << A.exp();

//    double values[9] = {1, 0, 0,
//                        0, 2, 0,
//                        0 ,0, 3};
//
//
//    Matrix A = Matrix(3, 3).fill_from_array(values);
//    Matrix B = A * 5;
//    Matrix C = A * B;
//
//    MatrixMemory A_mem = {5, 5};
    MatrixMemory A = {4, 4};
    std::cout << A.get_total_memory() << std::endl;

    return 0;
}