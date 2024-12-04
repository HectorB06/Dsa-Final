cmake_minimum_required(VERSION 3.29)
project(Dsa_Final_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Dsa_Final_main
        main.cpp
        max_heap.h
        min_heap.h
        student.cpp
        student.h)
