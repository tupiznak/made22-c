cmake_minimum_required(VERSION 3.14)
project(matrix_dot)

add_subdirectory(matrix_dot_lib)

message("MATRIX_DOT_LIB_INCLUDE_DIRS = ${MATRIX_DOT_LIB_INCLUDE_DIRS}")
message("MATRIX_DOT_LIB_LIBRARIES = ${MATRIX_DOT_LIB_LIBRARIES}")

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov")

target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_DOT_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${MATRIX_DOT_LIB_LIBRARIES})

enable_testing()
add_subdirectory(tests)
