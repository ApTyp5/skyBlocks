cmake_minimum_required(VERSION 3.5)
project(SkyBlocks VERSION 1)

set(SERVER ${PROJECT}_server)
set(CLIENT ${PROJECT}_client)
set(PARSER ${PROJECT}_parser)
add_subdirectory(parser)
add_subdirectory(server)
enable_testing()

add_executable(${SERVER} main.cpp)
