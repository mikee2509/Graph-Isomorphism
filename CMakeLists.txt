cmake_minimum_required(VERSION 3.6)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Graph.cpp Graph.h GraphLoader.cpp GraphLoader.h)
add_executable(Graphs ${SOURCE_FILES})