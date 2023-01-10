cmake_minimum_required(VERSION 3.23)
project(p_matrix)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_matrix Matrix.cpp MatrixTest.cpp MatrixTest.h MatrixException.cpp MatrixException.h Matrix.h main.cpp CMatrix.h CMatrix.cpp CMatrix.cpp)