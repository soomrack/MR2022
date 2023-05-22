cmake_minimum_required(VERSION 3.21)
project(programming)

set(CMAKE_CXX_STANDARD 20)

include_directories(abstract_data_types/2-linked_list)
include_directories(abstract_data_types/binary_tree)
include_directories(abstract_data_types/dynamic_array)
include_directories(abstract_data_types/FSM)
include_directories(abstract_data_types/graph)
include_directories(abstract_data_types/queue)
include_directories(abstract_data_types/stack)


add_executable(programming main.cpp
        abstract_data_types/2-linked_list/list.h
        abstract_data_types/binary_tree/tree.h
        abstract_data_types/dynamic_array/dynamic_array.h
        abstract_data_types/FSM/FSM.h
        abstract_data_types/graph/graph.h
        abstract_data_types/queue/queue.h
        abstract_data_types/stack/stack.h)