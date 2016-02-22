#-------------------------------------------------
#
# Project created by QtCreator 2016-02-05T21:28:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../../exe/formedit.e
TEMPLATE = app

LIBS += ../../../lib/libformular.so
INCLUDEPATH += ../../include

SOURCES += main.cpp\
        formulareditor.cpp \
    formularmodel.cpp

HEADERS  += formulareditor.h \
    formularmodel.h

FORMS    += formulareditor.ui
