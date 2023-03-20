cmake_minimum_required(VERSION 3.25)
project(Manipulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Manipulator main.cpp ../Arduino/Config.h graphics.h Connect.h Connect.cpp str.h str.cpp Gservo.h Gservo.cpp)

set(CMAKE_CXX_FLAGS "-lncurses")