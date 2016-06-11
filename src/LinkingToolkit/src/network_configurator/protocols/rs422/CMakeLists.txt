include_directories(${CMAKE_CURRENT_BINARY_DIR} . ../)

add_library(rs422 SHARED rs422_protocol.cpp)

target_link_libraries(rs422 ${QT_LIBRARIES})
