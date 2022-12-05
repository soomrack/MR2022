#include "MatrixTest.h"


[[maybe_unused]] inline void print_message(const std::string& text, const MatrixException& Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}


void MatrixTest::using_unused() {
    Matrix matrix(2, 2);
    matrix.fillFromVector(vector1);
    matrix.get_rows();
    matrix.get_cols();
    matrix.get_size();
    matrix.get_value(0, 0);
    MatrixException TEST(-15, "TEST");
    TEST.get_error_code();
}


void MatrixTest::calculation_check(double true_array[], Matrix *matrix, const std::string& text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int cell = 0; cell < matrix->size; cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix->values[cell]) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[cell];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix->values[cell] << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


void MatrixTest::output_test() {
    std::cout << "output test:" << std::endl;
    Matrix matrix1(2, 2);
    matrix1.fillFromVector(vector1);
    matrix1.output();
}


void MatrixTest::overload_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix res_matrix = matrix1;
        double eq_true_array[] = {2, 8, 1, 3};
        calculation_check(eq_true_array, &res_matrix, "= overload");
    }
    catch(MatrixException Exception_object) {
        print_message("overload_test", Exception_object);
    }
}


void MatrixTest::addition_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix matrix2(2, 2);
        matrix2.fillFromVector(vector2);
        Matrix res_matrix = matrix1 + matrix2;
        double sum_true_array[] = {6, 17, 22, 16};
        calculation_check(sum_true_array, &res_matrix, "addition (matrix)");
    }
    catch(MatrixException Exception_object) {
        print_message("addition_test", Exception_object);
    }
}


void MatrixTest::number_addition_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix res_matrix = matrix1 + 2;
        double snum_true_array[] = {4, 10, 3, 5};
        calculation_check(snum_true_array, &res_matrix, "addition (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_addition_test", Exception_object);
    }
}


void MatrixTest::subtraction_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix matrix2(2, 2);
        matrix2.fillFromVector(vector2);
        Matrix res_matrix = matrix1 - matrix2;
        double sub_true_array[] = {-2, -1, -20, -10};
        calculation_check(sub_true_array, &res_matrix, "subtraction");
    }
    catch(MatrixException Exception_object) {
        print_message("subtraction_test", Exception_object);
    }
}


void MatrixTest::multiplication_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix matrix2(2, 2);
        matrix2.fillFromVector(vector2);
        Matrix res_matrix = matrix1 * matrix2;
        double multi_true_array[] = {176, 122, 67, 48};
        calculation_check(multi_true_array, &res_matrix, "multiplication (matrix)");
    }
    catch(MatrixException Exception_object) {
        print_message("multiplication_test", Exception_object);
    }
}


void MatrixTest::number_multiplication_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix res_matrix = matrix1 * 2;
        double mnum_true_array[] = {4, 16, 2, 6};
        calculation_check(mnum_true_array, &res_matrix, "multiplication (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_multiplication_test", Exception_object);
    }
}


void MatrixTest::determinant_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        double determinant_true_array[] = {-2};
        Matrix det_matrix(1, 1, matrix1.determinant());
        calculation_check(determinant_true_array, &det_matrix, "determinant");
    }
    catch(MatrixException Exception_object) {
        print_message("determinant_test", Exception_object);
    }
}


void MatrixTest::transposition_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        double transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculation_check(transp_true_array, &res_matrix, "transposition");
    }
    catch(MatrixException Exception_object) {
        print_message("transposition_test", Exception_object);
    }
}


void MatrixTest::inversion_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        double inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculation_check(inv_true_array, &res_matrix, "inversion");
    }
    catch(MatrixException Exception_object) {
        print_message("inversion_test", Exception_object);
    }
}


void MatrixTest::inverse_multiplication_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix matrix2(2, 2);
        matrix2.fillFromVector(vector2);
        double inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculation_check(inv_multi_true_array, &res_matrix, "inverse multiplication");
    }
    catch(MatrixException Exception_object) {
        print_message("inverse_multiplication_test", Exception_object);
    }
}


void MatrixTest::number_division_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix res_matrix = matrix1 / 2;
        double snum_true_array[] = {1, 4, 0.5, 1.5};
        calculation_check(snum_true_array, &res_matrix, "division (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_division_test", Exception_object);
    }
}


void MatrixTest::power_test() {
    try {
        Matrix matrix1(2, 2);
        matrix1.fillFromVector(vector1);
        Matrix res_matrix = matrix1.power(power);
        calculation_check(power_array, &res_matrix, "power");
    }
    catch(MatrixException Exception_object) {
        print_message("power_test", Exception_object);
    }
}


void MatrixTest::exp_test() {
    try {
        Matrix matrix3(2, 2);
        matrix3.fillFromVector(vector3);
        double exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix res_matrix = Matrix::exp(matrix3);
        calculation_check(exp_true_array, &res_matrix, "Matrix exp");
    }
    catch(MatrixException Exception_object) {
        print_message("exp_test", Exception_object);
    }
}
