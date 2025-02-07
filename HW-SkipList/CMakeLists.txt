cmake_minimum_required(VERSION 3.27)
project(HW_SkipList)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW_SkipList main.cpp
        SkipList/SkipList.cpp
        RBTree/RBTree.cpp)
