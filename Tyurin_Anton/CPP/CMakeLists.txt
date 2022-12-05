cmake_minimum_required(VERSION 3.23)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled matrix.cpp Matrix_test.cpp Matrix_test.h matrix.h Matrix_exception.h Matrix_exception.cpp)
