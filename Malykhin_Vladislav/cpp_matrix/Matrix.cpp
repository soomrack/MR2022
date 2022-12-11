//
// Created by User on 05.12.2022.
//

#include "Matrix.h"


Matrix::Matrix() {
    rows = 0;
    columns = 0;
}

Matrix::Matrix(int input_rows, int input_columns, double number) {
    if (input_rows <= 0 || input_columns <= 0) {
        //  throw WRONG_PARAMETERS;
    }
    rows = input_rows;
    columns = input_columns;
    std::vector<std::vector<double>> buffer(rows, std::vector<double> (columns));
    cells = buffer;
    buffer.clear();
}

Matrix::Matrix(const Matrix &other) {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells;
}

Matrix::Matrix(Matrix &&other) noexcept {
    rows = other.rows;
    columns = other.columns;
    cells = other.cells; //  добавить проверку на nullptr
    other.rows = 0;
    other.columns = 0;
    other.cells.clear();
}

Matrix::~Matrix(){
    rows = 0;
    columns = 0;
    cells.clear();
}

void Matrix::vector_fill(std::vector<double> vector){
    if (rows*columns != vector.size()) {
      //  throw WRONG_LENGTH;
    }
    for(unsigned int row = 0; row < rows; row++)
        for (unsigned int col = 0; col < columns; ++col) {
           cells[row][col] = vector[col+row*(rows - 1)];
        }
}

void Matrix::vector_fill(const std::vector<std::vector<double>>& vector){
    if (cells.size() != vector.size()) {
        //  throw WRONG_LENGTH;
    }
    cells = vector;
}

void Matrix::set_identity() {
    if (rows != columns) {
       // throw NOT_SQUARE;
    }
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < columns; col++)
            cells[row][col] = (row == col) ? 1 : 0;
}


unsigned int Matrix::get_rows() const {
    return rows;
}


unsigned int Matrix::get_columns() const {
    return columns;
}


unsigned int Matrix::get_size() const {
    return columns * rows;
}


double Matrix::get_cell(int row, int column) const {
    if (row < 0 || column < 0) {
       // throw WRONG_PARAMETERS;
    }
    return cells[row][column];
}


