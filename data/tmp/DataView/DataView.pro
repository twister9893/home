QT += core gui

TARGET = DataView
DESTDIR = ../../exe/DataView

TEMPLATE = app

SOURCES += main.cpp \
    formular.cpp \
    dynamicformular.cpp \
    fielddata.cpp \
    dataview.cpp

HEADERS += \
    formular.h \
    fielddata.h \
    dynamicformular.h \
    dataview.h

FORMS += \
    dataview.ui

