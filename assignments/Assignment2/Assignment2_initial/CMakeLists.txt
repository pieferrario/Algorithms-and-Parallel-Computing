cmake_minimum_required(VERSION 4.3)
project(Assignment2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Assignment2 main.cpp
        Airport.cpp
        Airport.h
        Flight.cpp
        Flight.h
        Manager.cpp
        Manager.h
        Booking.h
        SingleBooking.h
        GroupBooking.h
        Passenger.h
        Booking.cpp)
