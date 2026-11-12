cmake_minimum_required(VERSION 3.16)
project(Employee)

set(CMAKE_CXX_STANDARD 14)

add_executable(Employee main.cpp
        Employee.h
        Employee.cpp
        Secretary.cpp
        Secretary.h
        Developer.cpp
        Developer.h
        Manager.cpp
        Manager.h)
