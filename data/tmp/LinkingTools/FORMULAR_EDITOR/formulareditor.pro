#-------------------------------------------------
#
# Project created by QtCreator 2015-06-21T21:27:10
#
#-------------------------------------------------

QT       += core xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = formulareditor
TEMPLATE = app

SOURCES += main.cpp\
    ../abstractfileeditor.cpp \
    formulareditor.cpp \
    ../fielddata.cpp \
    ../enumerationmodel.cpp \
    ../formularmodel.cpp \
    ../formulardelegate.cpp \
    ../enumerationelement.cpp \
    ../fielddataeditor.cpp \
    ../scalablewidget.cpp \
    ../enumerationwidget.cpp \
    ../constantwidget.cpp \
    ../enumerationdelegate.cpp

HEADERS  +=\
    ../abstractfileeditor.h \
    formulareditor.h \
    ../fielddata.h \
    ../enumerationmodel.h \
    ../formularmodel.h \
    ../formulardelegate.h \
    ../enumerationelement.h \
    ../fielddataeditor.h \
    ../scalablewidget.h \
    ../enumerationwidget.h \
    ../constantwidget.h \
    ../enumerationdelegate.h \
    ../libenum.h

FORMS    +=\
    formulareditor.ui \
    ../scalablewidget.ui \
    ../fielddataeditor.ui \
    ../enumerationwidget.ui \
    ../constantwidget.ui
