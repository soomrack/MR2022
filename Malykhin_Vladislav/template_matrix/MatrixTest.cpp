#include "MatrixTest.h"

inline void print_message(const std::string& text, const MatrixException& Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}

template<typename T>
void MatrixTest<T>::using_unused() {
    Matrix<T> matrix(2, 2, vector1);
    matrix.get_rows();
    matrix.get_columns();
    matrix.get_size();
    matrix.get_cell(0, 0);
    MatrixException TEST("TEST");
}

template<typename T>
void MatrixTest<T>::calculation_check(T true_array[], Matrix<T> *matrix, const std::string& text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int row = 0; row < matrix->get_rows(); row++)
        for (int column = 0; column < matrix->get_columns(); column++) {
        int cell_flag = 0;
        if (std::abs(true_array[row * matrix->get_columns() + column] - matrix->get_cell(row,column)) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[row * matrix->get_columns() + column];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix->get_cell(row,column) << " | " << cell_flag << "\n";
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}

template<typename T>
void MatrixTest<T>::output_test() {
    std::cout << "print test:" << std::endl;
    Matrix<T> matrix1(2, 2, vector1);
    matrix1.print();
}

template<typename T>
void MatrixTest<T>::overload_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> res_matrix = matrix1;
        T eq_true_array[] = {2, 8, 1, 3};
        calculation_check(eq_true_array, &res_matrix, "= overload");
    }
    catch(MatrixException &Exception_object) {
        print_message("overload_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::addition_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> matrix2(2, 2, vector2);
        Matrix<T> res_matrix = matrix1 + matrix2;
        T sum_true_array[] = {6, 17, 22, 16};
        calculation_check(sum_true_array, &res_matrix, "addition (matrix)");
    }
    catch(MatrixException &Exception_object) {
        print_message("addition_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::number_addition_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> res_matrix = matrix1 + 2;
        T snum_true_array[] = {4, 10, 3, 5};
        calculation_check(snum_true_array, &res_matrix, "addition (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_addition_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::subtraction_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> matrix2(2, 2, vector2);
        Matrix<T> res_matrix = matrix1 - matrix2;
        T sub_true_array[] = {-2, -1, -20, -10};
        calculation_check(sub_true_array, &res_matrix, "subtraction");
    }
    catch(MatrixException &Exception_object) {
        print_message("subtraction_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::multiplication_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> matrix2(2, 2, vector2);
        Matrix<T> res_matrix = matrix1 * matrix2;
        T multi_true_array[] = {176, 122, 67, 48};
        calculation_check(multi_true_array, &res_matrix, "multiplication (matrix)");
    }
    catch(MatrixException &Exception_object) {
        print_message("multiplication_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::number_multiplication_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> res_matrix = matrix1 * 2;
        T mnum_true_array[] = {4, 16, 2, 6};
        calculation_check(mnum_true_array, &res_matrix, "multiplication (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_multiplication_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::determinant_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        T determinant_true_array[] = {-2};
        Matrix<T> det_matrix(1, 1, matrix1.determinant());
        calculation_check(determinant_true_array, &det_matrix, "determinant");
    }
    catch(MatrixException &Exception_object) {
        print_message("determinant_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::transposition_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        T transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculation_check(transp_true_array, &res_matrix, "transposition");
    }
    catch(MatrixException &Exception_object) {
        print_message("transposition_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::inversion_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        T inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculation_check(inv_true_array, &res_matrix, "inversion");
    }
    catch(MatrixException &Exception_object) {
        print_message("inversion_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::inverse_multiplication_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> matrix2(2, 2, vector2);
        T inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculation_check(inv_multi_true_array, &res_matrix, "inverse multiplication");
    }
    catch(MatrixException &Exception_object) {
        print_message("inverse_multiplication_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::number_division_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> res_matrix = matrix1 / 2;
        T snum_true_array[] = {1, 4, 0.5, 1.5};
        calculation_check(snum_true_array, &res_matrix, "division (number)");
    }
    catch(MatrixException &Exception_object) {
        print_message("number_division_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::power_test() {
    try {
        Matrix<T> matrix1(2, 2, vector1);
        Matrix<T> res_matrix = matrix1.power(power);
        calculation_check(power_array, &res_matrix, "power");
    }
    catch(MatrixException &Exception_object) {
        print_message("power_test", Exception_object);
    }
}

template<typename T>
void MatrixTest<T>::exp_test() {
    try {
        Matrix<T> matrix3(2, 2, vector3);
        T exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix<T> res_matrix = Matrix<T>::exp(matrix3);
        calculation_check(exp_true_array, &res_matrix, "Matrix exp");
    }
    catch(MatrixException &Exception_object) {
        print_message("exp_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::counter_test() {
    std::cout << "CMatrix counter:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        if (CMatrix<T>::get_counter() != 0) {
            flag = 1;
        }
        CMatrix<T> matrix1;
        if (CMatrix<T>::get_counter() != 1) {
            flag = 1;
        }
        CMatrix<T> matrix2;
        if (CMatrix<T>::get_counter() != 2) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("eounter_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::matrix_mem_test() {
    std::cout << "CMatrix matrix memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        CMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.get_mem_size() != 192 && matrix1.get_mem_size() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("matrix_mem_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::gen_mem_test() {
    std::cout << "CMatrix general memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        CMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.get_mem_size() != 192 && matrix1.get_mem_size() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        print_message("matrix_gen_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::full_test(){
    MatrixTest<T>::using_unused();
    MatrixTest<T>::output_test();
    MatrixTest<T>::overload_test();
    MatrixTest<T>::addition_test();
    MatrixTest<T>::number_addition_test();
    MatrixTest<T>::subtraction_test();
    MatrixTest<T>::multiplication_test();
    MatrixTest<T>::number_multiplication_test();
    MatrixTest<T>::determinant_test();
    MatrixTest<T>::transposition_test();
    MatrixTest<T>::inversion_test();
    MatrixTest<T>::inverse_multiplication_test();
    MatrixTest<T>::number_division_test();
    MatrixTest<T>::power_test();
    MatrixTest<T>::exp_test();
    MatrixTest<T>::counter_test();
    MatrixTest<T>::matrix_mem_test();
    MatrixTest<T>::gen_mem_test();
}

template class MatrixTest<double>;
template class MatrixTest<float>;