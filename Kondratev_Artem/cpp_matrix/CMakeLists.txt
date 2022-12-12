cmake_minimum_required(VERSION 3.22)
project(hello_world)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello_world Matrix.cpp MatrixTest.cpp MatrixTest.h MatrixException.cpp MatrixException.h Matrix.h main.cpp EMatrix.cpp EMatrix.h)
