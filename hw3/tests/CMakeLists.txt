cmake_minimum_required(VERSION 3.14)
project(test_container)

set(CMAKE_CXX_STANDARD 14)

option(USE_SANITIZERS "" ON)
if (USE_SANITIZERS)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0 \
        -Wall -Wpedantic -Wextra -Werror -fsanitize=address,undefined \
        -fno-sanitize-recover=all -fsanitize-undefined-trap-on-error")
else()
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fprofile-arcs -ftest-coverage -O0 \
        -Wall -Wpedantic -Wextra -Werror")
endif(USE_SANITIZERS)
unset(USE_SANITIZERS CACHE)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

file(GLOB SOURCES *.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${MATRIX_CALC_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MATRIX_CALC_LIB_LIBRARIES} GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})