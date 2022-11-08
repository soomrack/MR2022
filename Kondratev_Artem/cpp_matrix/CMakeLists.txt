cmake_minimum_required(VERSION 3.23)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_world Matrix.cpp Matrix_test.cpp Matrix_test.h Matrix_exception.cpp Matrix_exception.h Matrix.h main.cpp)
