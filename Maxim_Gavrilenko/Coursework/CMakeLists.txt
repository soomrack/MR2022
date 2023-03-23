cmake_minimum_required(VERSION 3.24)
project(MR2022)

set(CMAKE_GENERATOR "MINGW Makefiles")


add_executable(MR2022 client.cpp)

target_link_libraries(MR2022 ws2_32)