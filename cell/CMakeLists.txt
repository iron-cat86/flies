add_library(cell STATIC)
set(headers
    cell.h)
set(sources
    cell.cpp)
#----#
include_directories(/usr/include/x86_64-linux-gnu/qt5/QtWidgets)

target_sources(
    cell
    PRIVATE ${headers} ${sources})

target_include_directories(
    cell
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ) # TODO: extract public headers to separate dir
    
target_link_libraries(
    cell
    PUBLIC
    Qt5::Core 
    fly) 
#----#

