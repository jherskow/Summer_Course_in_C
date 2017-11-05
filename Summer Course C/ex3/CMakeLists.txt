cmake_minimum_required(VERSION 3.6)
project(ex3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES SudokuSolver.c GenericDFS.c SudokuTree.c)
add_executable(ex3 ${SOURCE_FILES})