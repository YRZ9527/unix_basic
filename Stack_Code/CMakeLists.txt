cmake_minimum_required(VERSION 3.20)
project(Stack_Code)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Stack_Code
        main.cpp
        Stack.cpp
        Stack.h)
