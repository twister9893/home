#QMAKE_CXXFLAGS += -std=c++11
QT += core

#CONFIG += c++11

TARGET = GlGraphicsEngine
DESTDIR = ../../../exe/TSI/Plugins

CONFIG += plugin

LIBS += -lglut -lGL -lGLU
INCLUDEPATH += ../../../src/include

TEMPLATE = lib

SOURCES += \
    #main.cpp \
    glgraphicsengine.cpp

HEADERS += \
    glgraphicsengine.h
