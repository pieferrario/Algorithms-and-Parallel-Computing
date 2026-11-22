cmake_minimum_required(VERSION 3.14)
project(InterpolationInitialCode)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(InterpolationInitialCode
        Interpolation.cpp
        Interpolation.h
        LinearInterpolation.cpp
        LinearInterpolation.h
        NearestNeighborInterpolation.h
        NearestNeighborInterpolation.cpp
        main.cpp
        StepWiseInterpolation.h
        StepWiseInterpolation.cpp
        Point.cpp
        Point.h
        )
