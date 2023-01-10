#include <stdio.h>
#include "matrix.h"

int main() {
    unsigned int operation_choice = 6;
    // Выбор арифметической операции, производимой с матрицами, где
    // 1 - Операция сложения матриц
    // 2 - Операция вычитания матриц
    // 3 - Операция умножения матриц
    // 4 - Операция вычисления определителя матрицы методом Гаусса
    // 5 - Операция вычисления определителя с помощью миноров
    // 6 - Операция вычисления обратной матрицы
    // 7 - Операция взятия матричной экспоненты
    Matrix first;
    Matrix second;
    Matrix result;
    create_random_size_matrix(&first, &second);
    printf("Matrix A:\n");
    print_matrix(first);
    printf("\nMatrix B:\n");
    print_matrix(second);
    switch (operation_choice) {
        case 1: {
            printf("\nA + B:\n");
            print_matrix(matrix_add(&result, first, second));
            is_ans_correct_add(result, first, second);
            break;
        }
        case 2: {
            printf("\nA - B:\n");
            print_matrix(matrix_sub(&result, first, second));
            is_ans_correct_sub(result, first, second);
            break;
        }
        case 3: {
            printf("\nA * B:\n");
            print_matrix(matrix_mult(&result, first, second));
            is_ans_correct_mult(result, first, second);
            break;
        }
        case 4: {
            printf("\n|A| = %f\n", matrix_det_gauss(&result, first));
            printf("\n|B| = %f\n", matrix_det_gauss(&result, second));
            break;
        }
        case 6: {
            printf("\nA^(-1):\n");
            print_matrix(matrix_inv(&result, first));
            is_ans_correct_inv(result, first);
            printf("\nB^(-1):\n");
            print_matrix(matrix_inv(&result, second));
            is_ans_correct_inv(result, second);
            break;
        }
        case 7: {
            printf("\nexp(A)\n");
            print_matrix(matrix_exp(&result, first));
            is_ans_correct_exp(result, first);
            printf("\nexp(B)\n");
            print_matrix(matrix_exp(&result, second));
            is_ans_correct_exp(result, second);
            break;
        }
        default: {
            printf("Chosen number of operation does not allowed\n");
            print_matrix(*create_null_matrix(&result));
            break;
        }
    }
    free_memory(first);
    free_memory(second);
    free_memory(result);
    return 0;
}