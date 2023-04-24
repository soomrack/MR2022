cmake_minimum_required(VERSION 3.23)
project(Cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Cpp1 "Dynamic Array.cpp")
add_executable(Cpp2 "Linked List.cpp" "Linked List.h")
add_executable(Cpp3 "Stack.cpp")
add_executable(Cpp4 "Queue.cpp")
add_executable(Cpp5 "Priority Queue.cpp")
add_executable(Cpp_test "test.cpp")
add_executable(Cpp_test0 "test0.cpp")
add_executable(Cpp_test1 "test1.cpp")
