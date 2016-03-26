
include_directories(${GDAL_INCLUDE_DIR} ${FREETYPE_INCLUDE_DIRS} ${FTGL_INCLUDE_DIR})
include_directories()
add_executable(map.e main.cpp)
target_link_libraries(map.e ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GDAL_LIBRARIES} ${FTGL_LIBRARIES} system zmq fastdb)

add_executable(makeprim makeprim.cpp)
add_executable(primsender primsender.cpp)

add_executable(mapsender.e mapsender.cpp)
target_link_libraries(mapsender.e system zmq fastdb)

add_executable(mapS57toGL.e mapS57toGL.cpp)
target_link_libraries(mapS57toGL.e ${OPENGL_LIBRARIES} ${GDAL_LIBRARIES} system zmq fastdb)