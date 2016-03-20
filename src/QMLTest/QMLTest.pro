TEMPLATE = app

QT += qml quick widgets
CONFIG += c++11

SOURCES += main.cpp \
    glwidget.cpp \
    glcontext.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    glwidget.h \
    glcontext.h
