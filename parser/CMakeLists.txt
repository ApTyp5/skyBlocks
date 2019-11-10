cmake_minimum_required(VERSION 3.15)
project(parser)

find_package(GTest REQUIRED)


set(CMAKE_CXX_STANDARD 11)

add_executable(test_parser test.cpp)
target_include_directories(test_parser ${GTEST_INCLUDE_DIRS})