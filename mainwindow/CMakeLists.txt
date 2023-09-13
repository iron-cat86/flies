add_library(mainwindow STATIC)
set(headers
    mainwindow.h)
set(sources
    mainwindow.cpp)
#----#
include_directories(/usr/include/x86_64-linux-gnu/qt5/QtWidgets)

target_sources(
    mainwindow
    PRIVATE ${headers} ${sources})

target_include_directories(
    mainwindow
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ) # TODO: extract public headers to separate dir
    
target_link_libraries(
    mainwindow
    PUBLIC
    Qt5::Core 
    Qt5::Widgets
    plant) 
#----#

