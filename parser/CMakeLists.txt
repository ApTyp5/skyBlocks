cmake_minimum_required(VERSION 3.14)
project(parser)

find_package(GTest REQUIRED)

include_directories(test_parser ${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(test_parser test.cpp Analyzers/PythonLikeAnalyzer.cpp Analyzers/PythonLikeAnalyzer.h Analyzers/RuPseudoAnalyzer.cpp Analyzers/RuPseudoAnalyzer.h Analyzers/EnPseudoAnalyzer.cpp Analyzers/EnPseudoAnalyzer.h)
