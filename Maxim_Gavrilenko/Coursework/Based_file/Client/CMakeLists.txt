cmake_minimum_required(VERSION 3.24)
project(client)


add_executable(client client.cpp)

target_link_libraries(client ws2_32)