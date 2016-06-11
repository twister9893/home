ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_NO_DEBUG)
ADD_DEFINITIONS(-DQT_SHARED)

SET (CMAKE_AUTOMOC ON)

QT4_WRAP_UI(UISrcs network_configurator.ui)

include_directories(${CMAKE_CURRENT_BINARY_DIR} .)

add_executable(network_configurator.e main.cpp network_configurator.cpp ${MOCSrcs} ${UISrcs})

target_link_libraries(network_configurator.e ${QT_LIBRARIES})

add_subdirectory(protocols)
