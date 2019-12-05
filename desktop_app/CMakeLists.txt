cmake_minimum_required(VERSION 3.5)

project(qt_desk LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall")

set(SOURCE_DIR "src")
set(UI_DIR "ui")
set(HEADERS_DIR "include")
set(LIBS_DIR "lib.linux")

include_directories(${SOURCE_DIR}/${HEADERS_DIR})

set(SOURCE_FILES
    ${SOURCE_DIR}/main.cpp
    ${SOURCE_DIR}/skyblockseditor.cpp
    ${SOURCE_DIR}/qtblocksjson.cpp
    )

set(HEADERS
    ${SOURCE_DIR}/${HEADERS_DIR}/skyblockseditor.h
    ${SOURCE_DIR}/${HEADERS_DIR}/qtblocksjson.h
    )

set(UI
    ${SOURCE_DIR}/${UI_DIR}/skyblockseditor.ui
    )

set(CMAKE_AUTOUIC_SEARCH_PATHS ${SOURCE_DIR}/${UI_DIR})

add_subdirectory(${LIBS_DIR}/blocks)
include_directories(${blocks_lib_INCLUDE_DIRS})

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(qt_desk
    ${SOURCE_FILES}
    ${HEADERS}
    ${UI}
)

target_link_libraries(qt_desk PRIVATE Qt5::Widgets Qt5::Network blocks_lib)
