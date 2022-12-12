#include "MatrixTest.h"


[[maybe_unused]] inline void printMessage(const std::string& text, const MatrixException& Exception_object) {
    std::cout << text << ":" << std::endl << Exception_object.getMessage() << std::endl << std::endl;
}

template<typename T>
void MatrixTest<T>::usingUnused() {
    Matrix<T> matrix(2, 2, vector1);
    matrix.setValue(0, 0, matrix.getValue(0, 0));
    matrix.getRows();
    matrix.getCols();
    matrix.getSize();
    matrix.getValue(0);
    MatrixException TEST("TEST");
    EMatrix<double> identity_matrix(1);
}


template<typename T>
void MatrixTest<T>::calculationCheck(T true_array[], Matrix<T> *matrix, const std::string& text) {
    int error_flag = 0;
    std::cout << text << " test:\n";
    for (int cell = 0; cell < matrix->getSize(); cell++) {
        int cell_flag = 0;
        if (std::abs(true_array[cell] - matrix->getValue(cell)) > EPSILON) {
            cell_flag = 1;
            error_flag += 1;
        }
        std::cout << "true: " << std::scientific << std::setw(13) << true_array[cell];
        std::cout << " res: " << std::scientific << std::setw(13) << matrix->getValue(cell) << " | ";
        std::cout << cell_flag << std::endl;
    }
    std::cout << "Errors: " << error_flag << "\n";
    std::cout << "\n";
}


template<typename T>
Matrix<T> MatrixTest<T>::createMatrix(const std::vector<T>& vector) {
    return Matrix<T> (2,2, vector);
}


template<typename T>
void MatrixTest<T>::outputTest() {
    std::cout << "output test:" << std::endl;
    Matrix matrix1 = createMatrix(vector1);
    matrix1.output();
}


template<typename T>
void MatrixTest<T>::overloadTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix res_matrix = matrix1;
        T eq_true_array[] = {2, 8, 1, 3};
        calculationCheck(eq_true_array, &res_matrix, "= overload");
    }
    catch(MatrixException &Exception_object) {
        printMessage("overloadTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::additionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix matrix2 = createMatrix(vector2);
        Matrix res_matrix = matrix1 + matrix2;
        T sum_true_array[] = {6, 17, 22, 16};
        calculationCheck(sum_true_array, &res_matrix, "addition (matrix)");
    }
    catch(MatrixException &Exception_object) {
        printMessage("additionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::numberAdditionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix res_matrix = matrix1 + 2;
        T snum_true_array[] = {4, 10, 3, 5};
        calculationCheck(snum_true_array, &res_matrix, "addition (number)");
    }
    catch(MatrixException &Exception_object) {
        printMessage("numberAdditionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::subtractionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix matrix2 = createMatrix(vector2);
        Matrix res_matrix = matrix1 - matrix2;
        T sub_true_array[] = {-2, -1, -20, -10};
        calculationCheck(sub_true_array, &res_matrix, "subtraction");
    }
    catch(MatrixException &Exception_object) {
        printMessage("subtractionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::multiplicationTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix matrix2 = createMatrix(vector2);
        Matrix res_matrix = matrix1 * matrix2;
        T multi_true_array[] = {176, 122, 67, 48};
        calculationCheck(multi_true_array, &res_matrix, "multiplication (matrix)");
    }
    catch(MatrixException &Exception_object) {
        printMessage("multiplicationTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::numberMultiplicationTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix res_matrix = matrix1 * 2;
        T mnum_true_array[] = {4, 16, 2, 6};
        calculationCheck(mnum_true_array, &res_matrix, "multiplication (number)");
    }
    catch(MatrixException &Exception_object) {
        printMessage("numberMultiplicationTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::determinantTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        T determinant_true_array[] = {-2};
        Matrix det_matrix(1, 1, matrix1.determinant());
        calculationCheck(determinant_true_array, &det_matrix, "determinant");
    }
    catch(MatrixException &Exception_object) {
        printMessage("determinantTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::transpositionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        T transp_true_array[] = {2, 1, 8, 3};
        Matrix res_matrix = matrix1.transposition();
        calculationCheck(transp_true_array, &res_matrix, "transposition");
    }
    catch(MatrixException &Exception_object) {
        printMessage("transpositionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::inversionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        T inv_true_array[] = {-1.5, 4, 0.5, -1};
        Matrix res_matrix = matrix1.inversion();
        calculationCheck(inv_true_array, &res_matrix, "inversion");
    }
    catch(MatrixException &Exception_object) {
        printMessage("inversionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::inverseMultiplicationTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix matrix2 = createMatrix(vector2);
        T inv_multi_true_array[] = {1.036496, -0.102189, 0.364963, -0.021897};
        Matrix res_matrix = matrix1 / matrix2;
        calculationCheck(inv_multi_true_array, &res_matrix, "inverse multiplication");
    }
    catch(MatrixException &Exception_object) {
        printMessage("inverseMultiplicationTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::numberDivisionTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix res_matrix = matrix1 / 2;
        T snum_true_array[] = {1, 4, 0.5, 1.5};
        calculationCheck(snum_true_array, &res_matrix, "division (number)");
    }
    catch(MatrixException &Exception_object) {
        printMessage("numberDivisionTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::powerTest() {
    try {
        Matrix matrix1 = createMatrix(vector1);
        Matrix res_matrix = matrix1.power(power);
        calculationCheck(power_array, &res_matrix, "power");
    }
    catch(MatrixException &Exception_object) {
        printMessage("powerTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::expTest() {
    try {
        Matrix matrix3 = createMatrix(vector3);
        T exp_true_array[] = {27.799075, 26.799075, 26.799075, 27.799075};
        Matrix res_matrix = Matrix<T>::exp(matrix3);
        calculationCheck(exp_true_array, &res_matrix, "Matrix exp");
    }
    catch(MatrixException &Exception_object) {
        printMessage("expTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::equalTest() {
    try {
        std::vector<T> eq_vector1 = {2.951365, 3.4599872, 3.4599872, 2.951365};
        std::vector<T> eq_vector2 = {2.951365, 3.4599873, 3.4599879, 2.951386};
        Matrix<T> matrix1 = createMatrix(eq_vector1);
        Matrix<T> matrix2 = createMatrix(eq_vector2);
        T eq_true_array[] = {1};
        Matrix<T> res_matrix(1, 1);
        int res = Matrix<T>::isEqual(matrix1, matrix2);
        res_matrix.setValue(0, res);
        calculationCheck(eq_true_array, &res_matrix, "Matrix equality");
    }
    catch(MatrixException &Exception_object) {
        printMessage("equalTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::counterTest() {
    std::cout << "EMatrix counter:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        if (EMatrix<T>::getCounter() != 0) {
            flag = 1;
        }
        EMatrix<T> matrix1;
        if (EMatrix<T>::getCounter() != 1) {
            flag = 1;
        }
        EMatrix<T> matrix2;
        if (EMatrix<T>::getCounter() != 2) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        printMessage("expTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::matrixMemTest() {
    std::cout << "EMatrix matrix memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        EMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.getMemSize() != 192 && matrix1.getMemSize() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        printMessage("matrixMemTest", Exception_object);
    }
}


template<typename T>
void MatrixTest<T>::genMemTest() {
    std::cout << "EMatrix general memory size:" << std::endl << "Errors: ";
    try {
        short flag = 0;
        EMatrix<T> matrix1(4, 5, 6.2);
        if (matrix1.getMemSize() != 192 && matrix1.getMemSize() != 112) {
            flag = 1;
        }
        std::cout << flag << std::endl << std::endl;
    }
    catch(MatrixException &Exception_object) {
        printMessage("matrix_gen_test", Exception_object);
    }
}


template class MatrixTest<double>;
template class MatrixTest<float>;
