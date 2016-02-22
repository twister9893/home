QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../../lib/formular
TEMPLATE = lib

INCLUDEPATH += ../../include

SOURCES += formular.cpp \
    fielddata.cpp

HEADERS  += formular.h \
    fielddata.h
