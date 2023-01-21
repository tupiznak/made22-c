cmake_minimum_required(VERSION 3.14)
project(matrix_calc)

add_subdirectory(matrix_calc_lib)

set("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

enable_testing()
add_subdirectory(tests)
