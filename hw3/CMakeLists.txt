cmake_minimum_required(VERSION 3.14)
project(container)

add_subdirectory(container_lib)

set("CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -Wall -Wpedantic -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

enable_testing()
add_subdirectory(tests)
