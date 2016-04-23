QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui

TARGET = ../../exe/tsicore.e
TEMPLATE = app

HEADERS += \
    geoline.h \
    geopoint.h \
    geopointarray.h \
    georect.h \
    glgeographics.h \
    glgeoprimitive.h \
    glmapregion.h \
    libCoord.h \
    sysmath.h \
    tsicore.h \
    tsigraphicsmanager.h \
    tsimapmanager.h \
    tsinotificationmanager.h \
    tsiprimarymanager.h \
    tsitargetsmanager.h \
    tsitoolsmanager.h

SOURCES += \
    libCoord.cpp \
    main.cpp \
    sysmath.cpp \
    tsigraphicsmanager.cpp \
    tsicore.cpp
