#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H
#include "matrix.h"

bool test_add();
bool test_subtract();
bool test_multiply();
bool test_divide_by_scalar();
bool test_triangle_matrix();
bool test_transposed();
bool test_determinant();
bool test_minor();
bool test_cofactor();
bool test_inverted();
bool test_pow();
bool test_exponent();

//Exception tests
bool test_exception_add();
bool test_exception_division_by_zero();
bool test_exception_not_square();
bool test_exception_matrix_boundary();
bool test_exception_too_high_pow_degree();

#endif //TEST_FUNCTIONS_H
