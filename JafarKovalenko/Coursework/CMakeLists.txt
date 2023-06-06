cmake_minimum_required(VERSION 3.25)
project(Coursework)

set(CMAKE_CXX_STANDARD 14)

add_executable(Coursework main.cpp server.cpp server.h worker.h worker.cpp)
