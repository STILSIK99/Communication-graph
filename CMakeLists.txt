cmake_minimum_required(VERSION 3.9)

set (PROJECT_NAME Communication)
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${SOURCE_PATH}/UI)

include(CMakePrintHelpers)

cmake_print_variables(CMAKE_AUTOUIC_SEARCH_PATHS)

project(${PROJECT_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(PROJECT_SOURCES


        ${SOURCE_PATH}/main.cpp
        ${SOURCE_PATH}/mainwindow.cpp
        ${SOURCE_PATH}/service.cpp
        ${SOURCE_PATH}/node.cpp


        ${SOURCE_PATH}/UI/mainwindow.ui

        ${INCLUDE_PATH}/mainwindow.h
        ${INCLUDE_PATH}/service.h
        ${INCLUDE_PATH}/node.h
)

add_subdirectory(src)

