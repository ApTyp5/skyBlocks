cmake_minimum_required(VERSION 3.15)
project(desktop_app)

set(CMAKE_CXX_STANDARD 17)

set(BLOCK_LIB_SOURCE_FILE
        blocks/Algorithm.cpp
        blocks/Block.cpp
        blocks/BlockFactory.cpp
        blocks/FuncBlock.cpp
        blocks/IfBlock.cpp
        blocks/IOBlock.cpp)

set(REQUESTS_LIB_SOURCE_FILE
        requests/ConcreteRequest.cpp
        requests/GetRequest.cpp
        requests/PostRequest.cpp
        requests/Request.cpp
        Connector.cpp)

add_library(blocks_lib STATIC ${BLOCK_LIB_SOURCE_FILE})

add_library(requests_lib STATIC ${REQUESTS_LIB_SOURCE_FILE})

find_package( GTest REQUIRED )

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests_gtest tests_gtest.cpp)

add_executable(tests_gmock tests_gmock.cpp)

target_link_libraries(tests_gtest ${GTEST_LIBRARIES} pthread)
target_link_libraries(tests_gmock -lgmock pthread)
target_link_libraries(tests_gtest blocks_lib requests_lib)
target_link_libraries(tests_gmock blocks_lib requests_lib)

enable_testing()

add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gtest)
add_test(gtest ${EXECUTABLE_OUTPUT_PATH}/tests_gmock)