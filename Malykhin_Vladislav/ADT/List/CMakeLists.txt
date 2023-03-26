cmake_minimum_required(VERSION 3.23)
project(List)

set(CMAKE_CXX_STANDARD 17)

add_executable(ListTest.h ListTest.cpp Node.h List.cpp List.h main.cpp)