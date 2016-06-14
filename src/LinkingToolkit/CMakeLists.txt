cmake_minimum_required (VERSION 2.6)
project(LinkingToolkit)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/exe")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")

set(CMAKE_CXX_FLAGS "-O2 -g -Wall")
set(CMAKE_C_FLAGS "-O2 -g -Wall")

IF (NOT CMAKE_CXX_COMPILER)
    MESSAGE(WARNING "g++ not found. Install g++!")
    MESSAGE(FATAL_ERROR "===================================\ng++ не найден. Установите самостоятельно g++!\n===================================")
ENDIF (NOT CMAKE_CXX_COMPILER)


FIND_PACKAGE(Qt4)
IF (NOT QT4_FOUND)
      MESSAGE(WARNING "Libqt4-dev not found. Install libqt4-dev!")
      MESSAGE(FATAL_ERROR "===================================\nLibqt4-dev не найден. Установите самостоятельно libqt4-dev!\n===================================")
ENDIF (NOT QT4_FOUND)
set(QT_USE_QTXML 1)
set(QT_USE_QTNETWORK 1)
set(QT_USE_QTDESIGNER 1)
INCLUDE(${QT_USE_FILE})

add_subdirectory(src)

FIND_PACKAGE(Doxygen)
 IF(DOXYGEN_FOUND)
    OPTION(DOXYGEN_WARN_UNDOC "Generate Doxygen warnings for undocumented members?")
    IF(DOXYGEN_WARN_UNDOC)
        SET(CMAKE_WARN_IF_UNDOCUMENTED "YES")
    ELSE(DOXYGEN_WARN_UNDOC)
        SET(CMAKE_WARN_IF_UNDOCUMENTED "NO")
    ENDIF(DOXYGEN_WARN_UNDOC)
    SET(DOXYGEN_INPUT ${PROJECT_SOURCE_DIR}/src)
    SET(DOXYGEN_EXAMPLES ${PROJECT_SOURCE_DIR}/doc_examples)
    SET(DOXYGEN_OUTPUT ${PROJECT_SOURCE_DIR}/docs)

    SET(DOXYGEN_HTML_INDEX ${PROJECT_SOURCE_DIR}/docs/html/index.html)

    CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    ADD_CUSTOM_COMMAND(OUTPUT ${DOXYGEN_HTML_INDEX} COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        MAIN_DEPENDENCY ${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        #DEPENDS system testsender testreader
        COMMENT "Generating API documentation with Doxygen" VERBATIM)

    ADD_CUSTOM_TARGET(doc ALL DEPENDS ${DOXYGEN_HTML_INDEX})

    ADD_CUSTOM_TARGET(docs COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile COMMENT "Generating API documentation with Doxygen" VERBATIM)
 ELSE(DOXYGEN_FOUND)
    MESSAGE(WARNING "Doxygen not found. Install Doxygen!")
    MESSAGE(FATAL_ERROR "===================================\nDoxygen не найден. Установите самостоятельно Doxygen!\n===================================")
ENDIF(DOXYGEN_FOUND)
