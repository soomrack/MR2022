#include "matrix_cpp.cpp"

double ADD_VAL[9] = { 0.0,1.0, 2.0,
                     1.0,3.0,5.0,
                     2.0,5.0,8.0 };

double SUB_VAL[9] = { 0.0,1.0, 2.0,
                     1.0,1.0,1.0,
                     2.0,1.0,0.0 };

double MUL_VAL[9] = { 0.0,14.0, 28.0,
                     0.0,20.0,40.0,
                     0.0,26.0,52.0 };

double MAT_VAL[9] = { 0.0,2.0, 2.0,
                     1.0,5.0,3.0,
                     2.0,3.0,4.0 };

double DET_VAL = -10;

double EXP_VAL[9] = { 91.183965,160.707182,231.230400,
                     160.707182,286.340779,409.974376,
                     231.230400,409.974376,589.718351 };

void check_add() {
    Matrix MAT_ADD;
    MAT_ADD.fill_val(3,3, ADD_VAL);
    
    Matrix A;
    A.fill_sum(3,3);
    
    Matrix B;
    B.fill_mult(3,3);
    
    Matrix res;
    res = A + B;
    
    if (res != MAT_ADD) {
        std::cout << "ERROR: ADDITION INCORRECT\n";
        return;
    }
    std::cout << "ADDITION CORRECT\n";
}
void check_sub() {
    Matrix MAT_SUB;
    MAT_SUB.fill_val(3,3, SUB_VAL);
    
    Matrix A;
    A.fill_sum(3,3);
    
    Matrix B;
    B.fill_mult(3, 3);
    
    Matrix res;
    res = A - B;
    if ( res != MAT_SUB) {
        std::cout << "ERROR: SUBTRACTION INCORRECT\n";
        return;
    }
    std::cout << "SUBTRACTION CORRECT\n";
}

void check_mult() {
    Matrix MAT_MUL;
    MAT_MUL.fill_val(3,3, MUL_VAL);
	
    Matrix A;
    A.fill_sum(3, 4);
    
    Matrix B;
    B.fill_mult(4, 3);

    Matrix res;
    res = A * B;
    if (res != MAT_MUL) {
        std::cout << "ERROR: MULTIPLICATION INCORRECT\n";
        return;
    }
	std::cout << "MULTIPLICATION CORRECT\n";
}

void check_det() {
	Matrix A;
	A.fill_val(3,3, MAT_VAL);
	
	double det_a = matx_det(A);
	if (det_a != DET_VAL) {
		printf("ERROR: DETERMINANT INCORRECT\n");
		return;
	}
	printf("DETERMINANT CORRECT\n");
}

void check_exp() {
	Matrix MAT_EXP;
	MAT_EXP.fill_val(3,3, EXP_VAL);

	Matrix A;
	A.fill_sum(3, 3);
	
	Matrix res = matrix_exp(A);
	if (res != MAT_EXP) {
		std::cout << "ERROR: EXPONENT INCORRECT\n";
		return;
	}
	std::cout << "EXPONENT CORRECT\n";
}

int main() {
    {
        check_add();
        check_sub();
		check_mult();
		check_det();
		check_exp();
    }
    return 0;
}
