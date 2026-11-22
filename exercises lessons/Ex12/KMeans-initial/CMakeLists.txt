cmake_minimum_required(VERSION 4.3)
project(KMeans_initial)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(KMeans_initial
        Centroid.cpp
        Centroid.h
        Clustering.cpp
        Clustering.h
        KMeans.cpp
        Point.cpp
        Point.h)
