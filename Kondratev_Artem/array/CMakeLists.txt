cmake_minimum_required(VERSION 3.22)
project(hello_world)

set(CMAKE_CXX_STANDARD 20)

add_executable(hello_world main.cpp Array.cpp Array.h ArrayException.cpp ArrayException.h)
