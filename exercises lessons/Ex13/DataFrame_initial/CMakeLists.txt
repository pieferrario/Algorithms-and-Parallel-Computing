cmake_minimum_required(VERSION 3.20)
project(DataFrame)

set(CMAKE_CXX_STANDARD 11)

add_executable(DataFrame
        main.cpp
        DataFrame.cpp
        DataFrame.h)