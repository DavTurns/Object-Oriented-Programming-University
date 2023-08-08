cmake_minimum_required(VERSION 3.24)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab2
        PREFIX_length.cpp
        PREFIX_length.h
        PREFIX_length_test.cpp)
