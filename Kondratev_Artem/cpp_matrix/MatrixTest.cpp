#include "MatrixTest.h"


inline void print_message(const std::string& text, const MatrixException& Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.get_message() << std::endl << std::endl;
}

template<typename T>
void MatrixTest<T>::using_unused() {
    Matrix<T> matrix(2, 2, vector1);
    matrix.set_value(0, 0, vector1[0]);
    matrix.get_value(0,0);
    matrix.get_rows();
    matrix.get_cols();
    matrix.get_size();
    matrix.get_value(0, 0);
    MatrixException TEST(-15, "TEST");
    TEST.get_error_code();
}


template<typename T>
void MatrixTest<T>::calculation_check(T true_array[], Matrix<T> *matrix, const std::string& text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int cell = 0; cell < matrix->get_size(); cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix->get_value(cell)) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[cell];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix->get_value(cell) << " | ";
        std::cout << cell_flag << std::endl;
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


template<typename T>
Matrix<T> MatrixTest<T>::create_matrix(const std::vector<T>& vector) {
    return Matrix<T> (2,2, vector);
}


template<typename T>
void MatrixTest<T>::output_test() {
    std::cout << "output test:" << std::endl;
    Matrix matrix1 = create_matrix(vector1);
    matrix1.output();
}


template<typename T>
void MatrixTest<T>::overload_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix res_matrix = matrix1;
        T eq_true_array[] = {2, 8, 1, 3};
        calculation_check(eq_true_array, &res_matrix, "= overload");
    }
    catch(MatrixException Exception_object) {
        print_message("overload_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::addition_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix matrix2 = create_matrix(vector2);
        Matrix res_matrix = matrix1 + matrix2;
        T sum_true_array[] = {6, 17, 22, 16};
        calculation_check(sum_true_array, &res_matrix, "addition (matrix)");
    }
    catch(MatrixException Exception_object) {
        print_message("addition_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::number_addition_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix res_matrix = matrix1 + 2;
        T snum_true_array[] = {4, 10, 3, 5};
        calculation_check(snum_true_array, &res_matrix, "addition (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_addition_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::subtraction_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix matrix2 = create_matrix(vector2);
        Matrix res_matrix = matrix1 - matrix2;
        T sub_true_array[] = {-2, -1, -20, -10};
        calculation_check(sub_true_array, &res_matrix, "subtraction");
    }
    catch(MatrixException Exception_object) {
        print_message("subtraction_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::multiplication_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix matrix2 = create_matrix(vector2);
        Matrix res_matrix = matrix1 * matrix2;
        T multi_true_array[] = {176, 122, 67, 48};
        calculation_check(multi_true_array, &res_matrix, "multiplication (matrix)");
    }
    catch(MatrixException Exception_object) {
        print_message("multiplication_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::number_multiplication_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix res_matrix = matrix1 * 2;
        T mnum_true_array[] = {4, 16, 2, 6};
        calculation_check(mnum_true_array, &res_matrix, "multiplication (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_multiplication_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::determinant_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        T determinant_true_array[] = {-2};
        Matrix det_matrix(1, 1, matrix1.determinant());
        calculation_check(determinant_true_array, &det_matrix, "determinant");
    }
    catch(MatrixException Exception_object) {
        print_message("determinant_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::transposition_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        T transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculation_check(transp_true_array, &res_matrix, "transposition");
    }
    catch(MatrixException Exception_object) {
        print_message("transposition_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::inversion_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        T inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculation_check(inv_true_array, &res_matrix, "inversion");
    }
    catch(MatrixException Exception_object) {
        print_message("inversion_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::inverse_multiplication_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix matrix2 = create_matrix(vector2);
        T inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculation_check(inv_multi_true_array, &res_matrix, "inverse multiplication");
    }
    catch(MatrixException Exception_object) {
        print_message("inverse_multiplication_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::number_division_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix res_matrix = matrix1 / 2;
        T snum_true_array[] = {1, 4, 0.5, 1.5};
        calculation_check(snum_true_array, &res_matrix, "division (number)");
    }
    catch(MatrixException Exception_object) {
        print_message("number_division_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::power_test() {
    try {
        Matrix matrix1 = create_matrix(vector1);
        Matrix res_matrix = matrix1.power(power);
        calculation_check(power_array, &res_matrix, "power");
    }
    catch(MatrixException Exception_object) {
        print_message("power_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::exp_test() {
    try {
        Matrix matrix3 = create_matrix(vector3);
        T exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix res_matrix = Matrix<T>::exp(matrix3);
        calculation_check(exp_true_array, &res_matrix, "Matrix exp");
    }
    catch(MatrixException Exception_object) {
        print_message("exp_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::equal_test() {
    try {
        std::vector<T> eq_vector1 = {2.951365, 3.4599872, 3.4599872, 2.951365};
        std::vector<T> eq_vector2 = {2.951365, 3.4599873, 3.4599879, 2.951386};
        Matrix<T> matrix1 = create_matrix(eq_vector1);
        Matrix<T> matrix2 = create_matrix(eq_vector2);
        T eq_true_array[] = {1};
        Matrix<T> res_matrix(1, 1);
        int res = Matrix<T>::is_equal(matrix1, matrix2);
        res_matrix.set_value(0, res);
        calculation_check(eq_true_array, &res_matrix, "Matrix equality");
    }
    catch(MatrixException Exception_object) {
        print_message("equal_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::counter_test() {
    std::cout << "EMatrix counter:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        if (EMatrix<T>::get_counter() != 0) {
            flag = 1;
        }
        EMatrix<T> matrix1;
        if (EMatrix<T>::get_counter() != 1) {
            flag = 1;
        }
        EMatrix<T> matrix2;
        if (EMatrix<T>::get_counter() != 2) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException Exception_object) {
        print_message("exp_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::matrix_mem_test() {
    std::cout << "EMatrix matrix memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        EMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.getMemSize() != 192 && matrix1.getMemSize() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException Exception_object) {
        print_message("matrix_mem_test", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::gen_mem_test() {
    std::cout << "EMatrix general memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        EMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.getMemSize() != 192 && matrix1.getMemSize() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException Exception_object) {
        print_message("matrix_gen_test", Exception_object);
    }
}


template class MatrixTest<double>;
template class MatrixTest<float>;
