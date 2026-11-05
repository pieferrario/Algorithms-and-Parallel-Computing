cmake_minimum_required(VERSION 3.10)
project(Exe_2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(main main.cpp Sales_archive.cpp Sales_data.cpp)
target_compile_options(main PRIVATE -Wall)