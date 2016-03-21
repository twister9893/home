QT += core gui opengl

TARGET = OpenGL

DESTDIR = ../../exe/OpenGL

TEMPLATE = app

#LIBS += -lglut -lGL -lGLU

SOURCES += main.cpp \
    glwindow.cpp

HEADERS += \
    glwindow.h \
    gltesselator.h

