#ADD_DEFINITIONS(${QT_DEFINITIONS})
#ADD_DEFINITIONS(-DQT_PLUGIN)
#ADD_DEFINITIONS(-DQT_NO_DEBUG)
#ADD_DEFINITIONS(-DQT_SHARED)

#SET (CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_BINARY_DIR} . ../include)

add_executable(akva.e main.cpp)
# ${MOCSrcs})

target_link_libraries(akva.e ${QT_LIBRARIES} connection)
