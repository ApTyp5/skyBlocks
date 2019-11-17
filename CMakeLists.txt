cmake_minimum_required(VERSION 3.13)
project(SkyBlocks VERSION 1)

set(SERVER ${PROJECT}_server)
set(CLIENT ${PROJECT}_client)

add_executable(${SERVER} main.cpp)
