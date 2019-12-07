cmake_minimum_required(VERSION 3.5)

set(SERVER_FILES ../parser/Tools/Meta.cpp ../parser/Tools/Meta.h DataBaseConnection.cpp DataBaseConnection.h JsonExtractor.cpp JsonExtractor.h)

add_library(serverStructures ${SERVER_FILES})