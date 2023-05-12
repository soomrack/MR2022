cmake_minimum_required(VERSION 3.23)
project(Cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cpp_DA "Dynamic Array.cpp")
add_executable(Cpp_LL "Linked List.cpp" "Linked List.h")
add_executable(Cpp_S "Stack.cpp")
add_executable(Cpp_Q "Queue.cpp")
add_executable(Cpp_PQ "Priority Queue.cpp")
add_executable(Cpp_BT "Binary Tree.cpp")
add_executable(Cpp_test "test.cpp")
add_executable(Cpp_test0 "test0.cpp")
add_executable(Cpp_test1 "test1.cpp")

