cmake_minimum_required(VERSION 3.5)

project(qt_desktop LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(qt_desktop
  main.cpp
  skyblockseditor.cpp
  skyblockseditor.h
  skyblockseditor.ui
)

target_link_libraries(qt_desktop PRIVATE Qt5::Widgets Qt5::Network)
