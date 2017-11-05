cmake_minimum_required(VERSION 3.6)
project(ex2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wvla -Werror -std=c99")

#set(SOURCE_FILES ex1/ex1.c)
#add_executable(ex1 ${SOURCE_FILES})

set(SOURCE_FILES ex2/MyString.c)
set(SOURCE_FILES ex2/MyString.h)
set(SOURCE_FILES ex2/ex2.c)
add_executable(ex2 ${SOURCE_FILES})