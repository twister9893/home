#ifndef TSIGRAPHICSMANAGER_H
#define TSIGRAPHICSMANAGER_H

#include <QMap>

#include "glgeographics.h"

class TsiGraphicsManager {
public:
    bool addGraphics(uint id, GlGeoGraphics *gelem);
    bool removeGraphics(uint id);

    void process();

private:
    QMap<uint,GlGeoGraphics*> m_graphics;
};

#endif // TSIGRAPHICSMANAGER_H
