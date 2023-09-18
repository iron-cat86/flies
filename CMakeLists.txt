cmake_minimum_required(VERSION 3.16)

project(flies LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(LD_LIBRARY_PATH /usr/lib/x86_64-linux-gnu)
SET(CMAKE_BUILD_TYPE RelWithDebInfo)
SET(Qt5Core_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Core)
SET(Qt5Gui_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Gui)
SET(Qt5Widgets_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Widgets)
SET(Qt5Svg_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Svg)
SET(Qt5PrintSupport_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5PrintSupport)
SET(Qt5Concurrent_DIR /usr/lib/x86_64-linux-gnu/cmake/Qt5Concurrent)

link_directories(/usr/lib/x86_64-linux-gnu)

set(CMAKE_AUTOMOC ON)

find_package(PkgConfig REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(${PROJECT_NAME} "main.cpp")

add_subdirectory(plant)
add_subdirectory(cell)
add_subdirectory(fly)
add_subdirectory(mainwindow)

target_sources(
    flies
    PRIVATE ${sources})

target_include_directories(
        flies
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        ) # TODO: extract public headers to separate dir

target_link_libraries(flies PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
    mainwindow
    )
set_target_properties(
    flies
    PROPERTIES
        AUTOMOC ON
        AUTOUIC ON
        AUTORCC ON)
