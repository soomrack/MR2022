cmake_minimum_required(VERSION 3.23)
project(Dynamic_array)

set(CMAKE_CXX_STANDARD 17)

add_executable(Dynamic_array DArray.cpp DArray.h DArrayException.cpp DArrayException.h DArrayTest.cpp DArrayTest.h main.cpp)