#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T21:27:10
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = linkingtools
TEMPLATE = app


SOURCES += main.cpp\
        linkingtools.cpp \
    fielddata.cpp \
    enumerationmodel.cpp \
    formularmodel.cpp \
    formulardelegate.cpp \
    enumerationelement.cpp \
    fielddataeditor.cpp \
    scalablewidget.cpp \
    enumerationwidget.cpp \
    constantwidget.cpp \
    enumerationdelegate.cpp \
    abstractfileeditor.cpp

HEADERS  += linkingtools.h \
    fielddata.h \
    enumerationmodel.h \
    formularmodel.h \
    formulareditor.h \
    formulardelegate.h \
    enumerationelement.h \
    fielddataeditor.h \
    scalablewidget.h \
    enumerationwidget.h \
    constantwidget.h \
    enumerationdelegate.h \
    libenum.h \
    abstractfileeditor.h

FORMS    += linkingtools.ui \
    formulareditor.ui \
    scalablewidget.ui \
    fielddataeditor.ui \
    enumerationwidget.ui \
    constantwidget.ui
