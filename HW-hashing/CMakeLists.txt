cmake_minimum_required(VERSION 3.27)
project(HW_hashing)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW_hashing main.cpp
        HashLPTable.h
        HashLPTable.cpp
        HashCuckooTable.cpp
        HashCuckooTable.h)
