add_library(fly STATIC)
set(headers
    fly.h)
set(sources
    fly.cpp)
#----#

include_directories(/usr/include/x86_64-linux-gnu/qt5/QtWidgets)

target_sources(
    fly
    PRIVATE ${headers} ${sources})

target_include_directories(
    fly
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ) # TODO: extract public headers to separate dir
    
target_link_libraries(
    fly
    PUBLIC 
    Qt5::Core) 
#----#

