cmake_minimum_required(VERSION 3.5)
project(stack)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest-master)
include_directories(googletest-master/googletest/include)
include_directories(googletest-master/googlemock/include)

option (RUN_TESTS OFF)
if (RUN_TESTS)
    add_executable(stack run_unittests.cpp stack_tests.cpp my_stack.cpp my_stack.h)
else()
    add_executable(stack main.cpp my_stack.cpp my_stack.h)
endif()

target_link_libraries(stack gtest gtest_main)