SET (CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR} . ../../include)

add_library(connection SHARED connection.cpp)

target_link_libraries(connection ${QT_LIBRARIES})
