cmake_minimum_required(VERSION 3.23)
project(MR2022)

set(CMAKE_CXX_STANDARD 23)

include_directories(Dynamic_Array)
include_directories(stack)
include_directories(two_linked_list)
include_directories(queue)
include_directories(bynary_tree)

include_directories(Fenwick)

add_executable(programming main.cpp Dynamic_Array/dynamicArray.h stack/stack.h two_linked_list/twoLinkedList.h queue/queue.h bynary_tree/bynaryTree.h Fenwick/main.cpp bynary_tree/newBynaryTree.h)

