cmake_minimum_required(VERSION 3.24)
project(m_cpp)

set(CMAKE_CXX_STANDARD 11)

add_executable(m_cpp main.cpp matrix.h matrix_exception.h matrix.cpp matrix_exception.cpp)
