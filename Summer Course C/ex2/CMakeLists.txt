cmake_minimum_required(VERSION 3.6)
project(ex2)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wall -Wvla -std=c99")

#set(SOURCE_FILES MyString.c MyString.h LineSeparator.c LineSeparator.h MyStringExample.c)
#set(SOURCE_FILES LineSeparator.c LineSeparator.h)
set(SOURCE_FILES MyString.c MyString.h MyStringExample.c)

add_executable(ex2 ${SOURCE_FILES})