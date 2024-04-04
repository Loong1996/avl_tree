cmake_minimum_required(VERSION 3.10)

project(avl_tree)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(avl_tree
avl_tree.h
avl_tree_view.h
avl_tree_test.h
avl_tree_test.cpp
main.cpp
)