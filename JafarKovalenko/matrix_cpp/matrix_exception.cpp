#include "matrix_exception.h"
#include <iostream>

Matrix_exception::Matrix_exception(){
    this->error_code = 0;
};
Matrix_exception::Matrix_exception(int code){
    this->error_code = code;
};

void Matrix_exception::what() const{
    switch (this->error_code){
    case 1:
        std:: cout << "\nMatrices must be the same size\n" << std::endl;
        break;
    case 2:
        std::cout << "\nThe number of columns of the first matrix must be equal to " <<
        "the number of rows of the second matrix\n" << std::endl;
        break;
    case 3:
        std::cout << "\nThe matrix must be square\n" << std::endl;
        break;
    case 4:
        std::cout << "\nThe row and column of the minor are out of range\n" << std::endl;
        break;
    case 5:
        std::cout << "\nCan't diagonalize_matrix\n" << std::endl;
        break;
    default:
    std::cout << "\nUnknown error\n" << std::endl;
    }
}