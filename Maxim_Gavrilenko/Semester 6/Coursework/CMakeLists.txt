cmake_minimum_required(VERSION 3.23)
project(MR2022)


add_executable(MR2022 server.cpp)

target_link_libraries(MR2022 ws2_32)