#include "matrix_cpp_template.h"

int main(){

    double data[9] = {1, -2, 1,
                      2, 1, -1,
                      3, 2, -2};
    double ans_data[9] = {0, 2, -1,
                          -1, 5, -3,
                          -1, 8, -5};
    Matrix matrix = Matrix<double>(3, 3).fill_from_array(data);
    Matrix ans = Matrix<double>(3, 3).fill_from_array(ans_data);
    if (matrix.inv() == ans) std::cout << "Inverse matrix test successfully passed"<<std::endl;
    else std::cout<< "Inverse matrix test hasn't been successfully passed\n";



    return 0;
}
