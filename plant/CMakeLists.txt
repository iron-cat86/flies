add_library(plant STATIC)
set(headers
    plant.h)
set(sources
    plant.cpp)
#----#
target_sources(
    plant
    PRIVATE ${headers} ${sources})

target_include_directories(
    plant
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ) # TODO: extract public headers to separate dir
    
target_link_libraries(
    plant
    PUBLIC
    Qt5::Core 
    cell) 
#----#

