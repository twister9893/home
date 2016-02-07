QT += core gui

TARGET = TSI_GE
#CONFIG += plugin

LIBS += /usr/lib/libGL.so /usr/lib/libglut.so /usr/lib/libGLEW.so

TEMPLATE = app

SOURCES += main.cpp \
    glwindow.cpp \
    glengine.cpp \
    glgraphicsengine.cpp

HEADERS += \
    glwindow.h \
    glengine.h \
    glgraphicsengine.h

