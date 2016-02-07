#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T11:57:41
#
#-------------------------------------------------
QMAKE_CXXFLAGS += -std=c++11
QT       += core

TARGET = TsiCore
DESTDIR = ../../../exe/TSI
LIBS += -ldl -fPIC

TEMPLATE = app


SOURCES += main.cpp \
    tsicore.cpp \
    tsipluginloader.cpp

HEADERS += \
    Interfaces/tsiplugininterface.h \
    Interfaces/tsidatabaseinterface.h \
    Interfaces/tsimaploaderinterface.h \
    Interfaces/tsigraphicsengineinterface.h \
    tsicore.h \
    tsigraphics.h \
    tsiprimitive.h \
    tsipluginloader.h
