cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 23)

add_executable(Matrix_exception.cpp ../Template/main.cpp ../Template/Matrix.h ../Template/Matrix_test.cpp ../Template/Matrix_test.h ../Template/Matrix_exception.cpp ../Template/Matrix_exception.h Matrix.h ../Dynamic_array/main.cpp)
