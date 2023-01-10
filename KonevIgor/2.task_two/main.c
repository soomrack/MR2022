#include <stdio.h>
#include <malloc.h>
#include "matrix.h"

int main() {
    unsigned int operation_choice = 4;
    // Выбор арифметической операции, производимой с матрицами, где
    // 1 - Операция сложения матриц
    // 2 - Операция вычитания матриц
    // 3 - Операция умножения матриц
    // 4 - Операция вычисления определителя с помощью миноров
    // 5 - Операция вычисления обратной матрицы
    // 6 - Операция взятия матричной экспоненты
    Matrix first;
    Matrix second;
    Matrix result;
    create_random_size_matrix(&first, &second);
    printf("Matrix A:\n");
    print_matrix(first);
    printf("\nMatrix B:\n");
    print_matrix(second);
    printf("\n");
    switch (operation_choice) {
        case 1: {
            printf("\nA + B:\n");
            print_matrix(matrix_add(&result, first, second));
            if (is_ans_correct_add(result, first, second)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            break;
        }
        case 2: {
            printf("\nA - B:\n");
            print_matrix(matrix_sub(&result, first, second));
            if (is_ans_correct_sub(result, first, second)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            break;
        }
        case 3: {
            printf("\nA * B:\n");
            print_matrix(matrix_mult(&result, first, second));
            if (is_ans_correct_mult(result, first, second)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            break;
        }
        case 4: {
            printf("\n|A| = %f\n", matrix_det_gauss(&result, first));
            printf("\n|B| = %f\n", matrix_det_gauss(&result, second));
            break;
        }
        case 5: {
            printf("\nA^(-1):\n");
            print_matrix(matrix_inv(&result, first));
            if (is_ans_correct_inv(result, first)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            printf("\nB^(-1):\n");
            print_matrix(matrix_inv(&result, second));
            if (is_ans_correct_inv(result, second)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            break;
        }
        case 6: {
            printf("\nexp(A)\n");
            print_matrix(matrix_exp(&result, first));
            if (is_ans_correct_exp(result, first)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
            printf("\nexp(B)\n");
            print_matrix(matrix_exp(&result, second));
            if (is_ans_correct_exp(result, second)) {
                printf("The answer is correct.\n");
            } else
                printf("The answer is incorrect.\n");
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