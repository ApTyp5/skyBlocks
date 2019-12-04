cmake_minimum_required(VERSION 3.5)
project(blocks_library)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR "src")
set(TESTS_DIR "tests")

set(BLOCKS_LIB_SOURCE_FILES
        ${SRC_DIR}/Algorithm.cpp
        ${SRC_DIR}/Block.cpp
        ${SRC_DIR}/BlockFactory.cpp
        ${SRC_DIR}/FuncBlock.cpp
        ${SRC_DIR}/IfBlock.cpp
        ${SRC_DIR}/IOBlock.cpp)

add_library(blocks_lib STATIC ${BLOCKS_LIB_SOURCE_FILES})

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_gtest ${TESTS_DIR}/tests_gtest.cpp)

add_executable(tests_gmock ${TESTS_DIR}/tests_gmock.cpp)

target_link_libraries(tests_gtest ${GTEST_LIBRARIES} pthread)
target_link_libraries(tests_gmock -lgmock pthread)
target_link_libraries(tests_gtest blocks_lib requests_lib)
target_link_libraries(tests_gmock blocks_lib requests_lib)

enable_testing()

add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gmock)
