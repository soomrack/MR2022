cmake_minimum_required(VERSION 3.23)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

add_executable(matrix.cpp exceptions.cpp test.cpp main.cpp matrix.h exceptions.h test.h)
