cmake_minimum_required(VERSION 3.10)
project(main)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(
  -Wall
  -Werror
  -Wextra
  -Wno-deprecated
  -Winit-self
  -Wsign-conversion
  -Wredundant-decls
  -Wvla
  -Wshadow
  -Wctor-dtor-privacy
  -Wnon-virtual-dtor
  -Woverloaded-virtual
  -Wpointer-arith
  -Wcast-qual
  -Wcast-align
  -Wdouble-promotion
  -Wold-style-cast
  -Wno-error=old-style-cast
  -Wsign-promo
  -Wswitch-enum
  -Wswitch-default
  -Wundef
)

set(SOURCES
  main.cpp
  utils.cpp
  CSRMatrix.cpp
  JacobiPreconditioner.cpp
  CGSolver.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
