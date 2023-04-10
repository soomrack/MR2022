cmake_minimum_required(VERSION 3.23)
project(Cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cpp "test dm.cpp")
add_executable(Cpp1 "Dynamic Array.cpp")
add_executable(Cpp2 "Linked List.cpp")
add_executable(Cpp3 "Stack.cpp")
