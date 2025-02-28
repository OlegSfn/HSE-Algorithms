cmake_minimum_required(VERSION 3.27)
project(HW_dijkstra_vs_AStar)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW_dijkstra_vs_AStar main.cpp
        graph.cpp
        graph.h)
