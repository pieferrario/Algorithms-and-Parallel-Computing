cmake_minimum_required(VERSION 4.0)
project(SweetsBox)

set(CMAKE_CXX_STANDARD 20)

add_executable(SweetsBox main.cpp
        SweetsBox.hpp
        SweetsBox.cpp
        SweetsSock.hpp
        SweetsSock.cpp)
