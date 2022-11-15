cmake_minimum_required(VERSION 3.23)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_world Matrix.cpp MatrixTest.cpp MatrixTest.h MatrixException.cpp MatrixException.h Matrix.h main.cpp)
