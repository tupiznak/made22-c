cmake_minimum_required(VERSION 3.0.0)
project(matrix_dot_lib)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(MATRIX_DOT_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(MATRIX_DOT_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)
