cmake_minimum_required(VERSION 3.10)
project(red_black_tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(red_black_tree_test src/red_black_tree_test.cpp include/red_black_tree.h)

target_include_directories(red_black_tree_test PRIVATE include/)