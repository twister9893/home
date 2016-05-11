QT       += core gui xml opengl

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
    tsitoolsmanager.h \
    ito_object.h \
    style.h \
    line.h \
    geo.h \
    rect.h \
    ito_point.h \
    point.h \
    ito_primitive.h \
    ito_line.h \
    ito_rect.h \
    ito_polyline.h \
    ito_polygon.h \
    ito_ellipse.h \
    ito_arc.h \
    ito_sector.h

SOURCES += \
    libCoord.cpp \
    main.cpp \
    sysmath.cpp \
    tsigraphicsmanager.cpp \
    tsicore.cpp
