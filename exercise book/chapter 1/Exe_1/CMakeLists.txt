cmake_minimum_required(VERSION 3.15)
project(Exe_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Exe_1
        main.cpp
        Stock_quote.cpp
        Stock_quote_archive.cpp
)