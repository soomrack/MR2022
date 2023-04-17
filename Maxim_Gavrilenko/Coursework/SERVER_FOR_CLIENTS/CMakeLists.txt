cmake_minimum_required(VERSION 3.24)
project(MR2022)


add_executable(MR2022 ../../Binary_Tree/binary.cpp ../../Graph/Graph.h)

target_link_libraries(MR2022 ws2_32)