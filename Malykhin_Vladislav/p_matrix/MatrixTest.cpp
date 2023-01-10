#include "MatrixTest.h"

inline void print_message(const std::string& text, const MatrixException& Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}

void MatrixTest::using_unused() {
    Matrix matrix(2, 2, vector1);
    matrix.get_rows();
    matrix.get_cols();
    matrix.get_size();
    matrix.get_cell(0, 0);
    MatrixException TEST("TEST");
}

void MatrixTest::calculation_check(double true_array[], Matrix *matrix, const std::string& text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int row = 0; row < matrix->get_rows(); row++)
        for (int column = 0; column < matrix->get_cols(); column++) {
        int cell_flag = 0;
        if (std::abs(true_array[row * matrix->get_cols() + column] - matrix->get_cell(row,column)) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[row * matrix->get_cols() + column];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix->get_cell(row,column) << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


void MatrixTest::output_test() {
    std::cout << "print test:" << std::endl;
    Matrix matrix1(2, 2, vector1);
    matrix1.print();
}


void MatrixTest::overload_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix res_matrix = matrix1;
        double eq_true_array[] = {2, 8, 1, 3};
        calculation_check(eq_true_array, &res_matrix, "= overload");
    }
    catch(MatrixException &Exception_object) {
        print_message("overload_test", Exception_object);
    }
}


void MatrixTest::addition_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix matrix2(2, 2, vector2);
        Matrix res_matrix = matrix1 + matrix2;
        double sum_true_array[] = {6, 17, 22, 16};
        calculation_check(sum_true_array, &res_matrix, "addition (matrix)");
    }
    catch(MatrixException &Exception_object) {
        print_message("addition_test", Exception_object);
    }
}


void MatrixTest::number_addition_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix res_matrix = matrix1 + 2;
        double snum_true_array[] = {4, 10, 3, 5};
        calculation_check(snum_true_array, &res_matrix, "addition (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_addition_test", Exception_object);
    }
}


void MatrixTest::subtraction_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix matrix2(2, 2, vector2);
        Matrix res_matrix = matrix1 - matrix2;
        double sub_true_array[] = {-2, -1, -20, -10};
        calculation_check(sub_true_array, &res_matrix, "subtraction");
    }
    catch(MatrixException &Exception_object) {
        print_message("subtraction_test", Exception_object);
    }
}


void MatrixTest::multiplication_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix matrix2(2, 2, vector2);
        Matrix res_matrix = matrix1 * matrix2;
        double multi_true_array[] = {176, 122, 67, 48};
        calculation_check(multi_true_array, &res_matrix, "multiplication (matrix)");
    }
    catch(MatrixException &Exception_object) {
        print_message("multiplication_test", Exception_object);
    }
}


void MatrixTest::number_multiplication_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix res_matrix = matrix1 * 2;
        double mnum_true_array[] = {4, 16, 2, 6};
        calculation_check(mnum_true_array, &res_matrix, "multiplication (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_multiplication_test", Exception_object);
    }
}


void MatrixTest::determinant_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        double determinant_true_array[] = {-2};
        Matrix det_matrix(1, 1, matrix1.determinant());
        calculation_check(determinant_true_array, &det_matrix, "determinant");
    }
    catch(MatrixException &Exception_object) {
        print_message("determinant_test", Exception_object);
    }
}


void MatrixTest::transposition_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        double transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculation_check(transp_true_array, &res_matrix, "transposition");
    }
    catch(MatrixException &Exception_object) {
        print_message("transposition_test", Exception_object);
    }
}


void MatrixTest::inversion_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        double inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculation_check(inv_true_array, &res_matrix, "inversion");
    }
    catch(MatrixException &Exception_object) {
        print_message("inversion_test", Exception_object);
    }
}


void MatrixTest::inverse_multiplication_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix matrix2(2, 2, vector2);
        double inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculation_check(inv_multi_true_array, &res_matrix, "inverse multiplication");
    }
    catch(MatrixException &Exception_object) {
        print_message("inverse_multiplication_test", Exception_object);
    }
}


void MatrixTest::number_division_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix res_matrix = matrix1 / 2;
        double snum_true_array[] = {1, 4, 0.5, 1.5};
        calculation_check(snum_true_array, &res_matrix, "division (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_division_test", Exception_object);
    }
}


void MatrixTest::power_test() {
    try {
        Matrix matrix1(2, 2, vector1);
        Matrix res_matrix = matrix1.power(power);
        calculation_check(power_array, &res_matrix, "power");
    }
    catch(MatrixException &Exception_object) {
        print_message("power_test", Exception_object);
    }
}


void MatrixTest::exp_test() {
    try {
        Matrix matrix3(2, 2, vector3);
        double  exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix res_matrix = Matrix::exp(matrix3);
        calculation_check(exp_true_array, &res_matrix, "Matrix exp");
    }
    catch(MatrixException &Exception_object) {
        print_message("exp_test", Exception_object);
    }
}



void MatrixTest::counter_test() {
    std::cout << "CMatrix counter:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        if (CMatrix::get_counter() != 0) {
            flag = 1;
        }
        CMatrix matrix1;
        if (CMatrix::get_counter() != 1) {
            flag = 1;
        }
        CMatrix matrix2;
        if (CMatrix::get_counter() != 2) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("eounter_test", Exception_object);
    }
}



void MatrixTest::matrix_mem_test() {
    std::cout << "CMatrix matrix memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        CMatrix matrix1(4, 5, 6.2);
        if (matrix1.get_mem_size() != 192 && matrix1.get_mem_size() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("matrix_mem_test", Exception_object);
    }
}



void MatrixTest::gen_mem_test() {
    std::cout << "CMatrix general memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        CMatrix matrix1(4, 5, 6.2);
        if (matrix1.get_mem_size() != 192 && matrix1.get_mem_size() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("matrix_gen_test", Exception_object);
    }
}



void MatrixTest::full_test(){
    MatrixTest::using_unused();
    MatrixTest::output_test();
    MatrixTest::overload_test();
    MatrixTest::addition_test();
    MatrixTest::number_addition_test();
    MatrixTest::subtraction_test();
    MatrixTest::multiplication_test();
    MatrixTest::number_multiplication_test();
    MatrixTest::determinant_test();
    MatrixTest::transposition_test();
    MatrixTest::inversion_test();
    MatrixTest::inverse_multiplication_test();
    MatrixTest::number_division_test();
    MatrixTest::power_test();
    MatrixTest::exp_test();
    MatrixTest::counter_test();
    MatrixTest::matrix_mem_test();
    MatrixTest::gen_mem_test();
}