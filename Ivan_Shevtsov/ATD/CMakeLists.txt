cmake_minimum_required(VERSION 3.24)
project(ATD)

set(CMAKE_CXX_STANDARD 17)

add_executable(ATD main.cpp list.h stack.h dynamic_array.cpp dynamic_array.h queue.cpp queue.h tree.cpp tree.h graph.cpp graph.h)
