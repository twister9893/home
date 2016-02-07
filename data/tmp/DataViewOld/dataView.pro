QT += network \
    gui \
    xml
TARGET = ../../exe/DataView/dataview.e
TEMPLATE = app
LIBS += ../lib/libsysfunc.so \
    ../lib/glob_mat.so \
    ../lib/DTW.so \
    ../lib/libtb.so \
    ../lib/LinDB.so \
    ../lib/tinyxml.so \
    ../lib/libnmea.so
HEADERS += xmlparser.h \
    dataviewprog.h \
    AbonentList.h \
    DataView.h \
    TableModel.h \
    AbonentNetworkTool.h \
    project/AbonentGetDataFunctions.h \
    hvLib/HierarchicalHeaderView.h \
    additional.h \
    converter.h \
    fielddata.h \
    formular.h
SOURCES += xmlparser.cpp \
    dataviewprog.cpp \
    AbonentList.cpp \
    DataView.cpp \
    TableModel.cpp \
    AbonentNetworkTool.cpp \
    hvLib/HierarchicalHeaderView.cpp \
    additional.cpp \
    converter.cpp \
    fielddata.cpp \
    formular.cpp
FORMS += AbonentList.ui \
    DataView.ui
RESOURCES += icons.qrc
