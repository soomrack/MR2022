#include "matrix_cpp.h"


Matrix::Matrix() {
    //std::cout << "Constructor\n";
    cols = 1;
    rows = 1;
    values = new double[cols * rows];
    values[0] = NAN;
}

Matrix::Matrix(const Matrix &orig) {
    //std::cout << "Copy constructor\n";

    rows = orig.rows;
    cols = orig.cols;
    values = new double[rows * cols];

    for(int k = 0; k < rows * cols; k++){
        values[k] = orig.values[k];
    }
}

Matrix::Matrix(Matrix &&orig) noexcept{
	//std::cout << "Move constructor\n";

	rows = orig.rows;
	cols = orig.cols;
	values = orig.values;
	orig.rows = 0;
	orig.cols = 0;
	orig.values = nullptr;
}

Matrix::~Matrix() {
    //std::cout << "Deconstructor\n";
	delete[] values;
}

void Matrix::reset_mem(unsigned int set_rows, unsigned int set_cols) {
	//std::cout << "Reset mem\n";
	delete[] values;
    rows = set_rows;
    cols = set_cols;
    values = new double[rows * cols];
}

void Matrix::fill_sum(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = k % cols + (unsigned int)(k / cols);
    }
}

void Matrix::fill_mult(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows,set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = k % cols * (int)(k / cols);
    }
}

void Matrix::fill_val(unsigned int set_rows, unsigned int set_cols, const double *set_values) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = set_values[k];
    }
}

void Matrix::make_one(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        if((int)(k / cols) == (k % cols)){
            values[k] = 1.0;
        }
        else{
            values[k] = 0.0;
        }
    }
}

void Matrix::make_zero(unsigned int set_rows, unsigned int set_cols) {
    reset_mem(set_rows, set_cols);
    for(int k = 0; k < rows * cols; k++){
        values[k] = 0.0;
    }
}

void Matrix::change_rows(const int fst_row, const int snd_row) const {
    double item_buff;
    for (int col = 0; col < cols; col++) {
        item_buff = values[snd_row * cols + col];
        values[snd_row * cols + col] = values[fst_row * cols + col];
		values[fst_row * cols + col] = item_buff;
    }
}

void Matrix::print_values() const {
    std::cout << "\n";
    for(int k = 0; k < rows; k++){
        std::cout << "(";
        for(int j = 0; j < cols; j++){
            std::cout << values[k * cols + j] << ", ";
        }
        std::cout <<")\n";
    }
}

Matrix &Matrix::operator=(const Matrix& orig) {
	//std::cout << "Equal operator copy\n";
	if (this == &orig) return *this;
	reset_mem(orig.rows,orig.cols);
	for(int k = 0; k < rows * cols; k++){
		values[k] = orig.values[k];
	}
	return *this;
}

Matrix &Matrix::operator=(Matrix&& orig) noexcept{
	//std::cout << "Equal operator move\n";
	if (this == &orig) return *this;
	delete[] values;
	cols = orig.cols;
	rows = orig.rows;
	values = orig.values;
	orig.cols = 0;
	orig.rows = 0;
	orig.values = nullptr;
	return *this;
}

Matrix Matrix::operator+(Matrix const snd_matx) {
	if (rows != snd_matx.rows || cols != snd_matx.cols){
        message(ADD);
		throw WRONG_SIZE;
    }
	//std::cout << "Add operator\n";
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = values[k] + snd_matx.values[k];
    }
    return res_matx;
}

Matrix Matrix::operator-(const Matrix snd_matx) {
    if (rows != snd_matx.rows || cols != snd_matx.cols){
        message(SUB);
        throw WRONG_SIZE;
    }
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++){
        res_matx.values[k] = values[k] - snd_matx.values[k];
    }
    return res_matx;
}

Matrix Matrix::operator*(const Matrix snd_matx) {
	if (cols != snd_matx.rows){
        message(MUL);
		throw WRONG_SIZE;
    }
    Matrix res_matx;
    res_matx.make_zero(rows, snd_matx.cols);
    for(int k = 0; k < rows; k++) {
        for (int j = 0; j < snd_matx.get_cols(); j++) {
            for (int n = 0; n < cols; n++) {
                res_matx.values[k * snd_matx.cols + j] += values[k * cols + n] * snd_matx.values[n * snd_matx.cols + j];
			}
        }
    }
	return res_matx;
}

Matrix Matrix::operator*(double const a) const {
    Matrix res_matx;
    res_matx.make_zero(rows,cols);
    for(int k = 0; k < rows * cols; k++) {
        res_matx.values[k] = a * values[k];
    }
    return res_matx;
}

Matrix Matrix::operator / (double a)  const{
	if (a == 0) throw DIV_BY_ZERO;
	Matrix res_matx;
	res_matx.make_zero(rows,cols);
	for(int k = 0; k < rows * cols; k++) {
		res_matx.values[k] = values[k] / a;
	}
	return res_matx;
}

bool Matrix::operator==(const Matrix B) {
    if(cols != B.cols){
        return false;
    }
    if(rows != B.rows){
        return false;
    }
    for(int k = 0; k < cols * rows; k++){
        if (fabs(values[k] - B.values[k]) > EQUAL_ACCURACY) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix B) {
	if(cols != B.cols){
        return true;
    }
    if(rows != B.rows){
        return true;
    }
    for(int k = 0; k < cols * rows; k++){
        if (fabs(values[k] - B.values[k]) > EQUAL_ACCURACY) {
            return true;
        }
    }
    return false;
}

Matrix &Matrix::operator += (Matrix& snd_matx){
	*this = *this + snd_matx;
	return *this;
}

Matrix &Matrix::operator -= (Matrix& snd_matx){
	*this = *this - snd_matx;
	return *this;
}

unsigned int Matrix::get_rows() const{
	return rows;
}

unsigned int Matrix::get_cols() const{
	return cols;
}

double Matrix::get_value(unsigned int ind){
	return values[ind];
}

void Matrix::set_value(unsigned int ind, double val){
	values[ind] = val;
}

double* Matrix::get_values() {
	return values;
}

void Matrix::set_values(double* val) {
	values = val;
}


double Matrix::get_item(unsigned int row, unsigned int col) {
	return values[row * cols + col];
}

void Matrix::set_item(unsigned int row, unsigned int col, double val){
	values[row * cols + col] = val;
}

MemMatrix::MemMatrix(): Matrix(){
	//std::cout << "Mem Constructor\n";
	mat_mem = rows * cols * sizeof(double);
	FULL_MEM += mat_mem;
	OBJ_COUNT += 1;
	//print_mem();
}

MemMatrix::MemMatrix(const Matrix& orig): Matrix(orig){
	//std::cout << "Mem Copy constructor\n";
	mat_mem = rows * cols * sizeof(double);
	FULL_MEM += mat_mem;
	OBJ_COUNT += 1;
	//print_mem();
}
MemMatrix::MemMatrix(Matrix&& orig): Matrix(orig){
	//std::cout << "Mem Move constructor\n";
	mat_mem = rows * cols * sizeof(double);
	FULL_MEM += mat_mem;
	OBJ_COUNT += 1;
	//print_mem();
}
MemMatrix::~MemMatrix(){
	//std::cout << "Mem Deconstructor\n";
	FULL_MEM -= mat_mem;
	mat_mem = 0;
	OBJ_COUNT -= 1;
	//print_mem();
}

MemMatrix& MemMatrix::operator=(Matrix&& orig) noexcept {
	//std::cout << "Mem Equal operator move\n";
	if (this == &orig) return *this;
	delete[] values;
	cols = orig.get_cols();
	rows = orig.get_rows();
	values = orig.get_values();
	FULL_MEM -= mat_mem;
	mat_mem = rows * cols * sizeof(double);
	FULL_MEM += mat_mem;
	orig.set_values(nullptr);
	return *this;
}

void MemMatrix::reset_mem(unsigned int set_rows, unsigned int set_cols){
	std::cout << "Mem reset_mem\n";
	delete[] values;
	rows = set_rows;
	cols = set_cols;
	values = new double[rows * cols];
	FULL_MEM -= mat_mem;
	mat_mem = rows * cols * sizeof(double);
	FULL_MEM += mat_mem;
}

double matx_det(const Matrix matrix) {
    if(matrix.get_rows() != matrix.get_cols()){
        message(DET);
		throw NOT_SQUARE;
    }
    double det = 1;
    Matrix trian_mat;
    trian_mat = matrix;
    for(int row_fix = 1; row_fix < trian_mat.get_rows(); row_fix++) { // row that will be subtracted
        for (int row = row_fix; row < trian_mat.get_rows(); row++) { // start from the next row
            if (fabs(trian_mat.get_item(row_fix - 1,row_fix - 1)) < DETERMINANT_ACCURACY) { // division by zero check
                trian_mat.change_rows(row_fix - 1, row_fix);
                det = -det;
            }
            double koef = trian_mat.get_item(row, row_fix - 1) / trian_mat.get_item(row_fix - 1, row_fix - 1);
            for (int col = 0; col < trian_mat.get_cols(); col++) {
                double item_val = trian_mat.get_item(row, col) - trian_mat.get_item(row_fix - 1, col) * koef;
				trian_mat.set_item(row, col, item_val);
            }
        }
        det *= trian_mat.get_item(row_fix, row_fix);
    }
    return det;
}

double check_max_dif(Matrix* fst_mat, Matrix* snd_mat) {
    double dif = 0.0;
    for(int k = 0; k < fst_mat->get_cols() * fst_mat->get_rows(); k++){
        if(fabs(fst_mat->get_value(k) - snd_mat->get_value(k)) > dif){
            dif = fst_mat->get_value(k) - snd_mat->get_value(k);
        }
    }
    return dif;
}

Matrix matrix_exp(const Matrix* matrix) {
	if(matrix->get_rows() != matrix->get_cols()){
		message(EXP);
		throw NOT_SQUARE;
	}
	Matrix res_mat;
	res_mat.make_one(matrix->get_rows(),matrix->get_cols());
	Matrix member;
	member.make_one(matrix->get_rows(),matrix->get_cols());
	Matrix prev_mat;
	for(int m = 1; m <= EXPONENT_STEPS; m++){
		member = member * *matrix / m;
		res_mat += member;
		if(fabs(check_max_dif(&res_mat,&prev_mat)) < EXPONENT_ACCURACY){
			return res_mat;
		}
	}
	return res_mat;
}
