#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T11:57:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TSI
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    tsicore.cpp

HEADERS += \
    tsicore.h \
    Interfaces/tsidatabaseinterface.h \
    Interfaces/tsimaploaderinterface.h \
    Interfaces/tsigraphicsengineinterface.h
