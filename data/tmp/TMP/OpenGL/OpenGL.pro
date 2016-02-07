QT += core gui opengl svg

TARGET = OpenGL

DESTDIR = ../../../exe/TMP/OpenGL

TEMPLATE = app

#LIBS += -lglut -lGL -lGLU

SOURCES += main.cpp \
    glwindow.cpp

HEADERS += \
    glwindow.h

