SET (CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR} . ../../../include)

add_library(ethernet SHARED ethernet_interface.cpp)

target_link_libraries(ethernet ${QT_LIBRARIES})
