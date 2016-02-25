#-------------------------------------------------
#
# Project created by QtCreator 2016-02-05T21:28:47
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../../exe/formedit.e
TEMPLATE = app

SOURCES += main.cpp\
        formulareditor.cpp \
    formularmodel.cpp

HEADERS  += formulareditor.h \
    formularmodel.h

FORMS    += formulareditor.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../lib/release/ -lformular
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../lib/debug/ -lformular
else:unix: LIBS += -L$$PWD/../../../lib/ -lformular

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
