#include "tsigraphicsmanager.h"

bool TsiGraphicsManager::addGraphics(uint id, GlGeoGraphics *gelem)
{
    if(m_graphics.find(id)==m_graphics.end())
        m_graphics.insert(id,gelem);
    else
        m_graphics[id]=gelem;

    return true;
}

bool TsiGraphicsManager::removeGraphics(uint id)
{
    return m_graphics.remove(id);
}

void TsiGraphicsManager::process()
{
    foreach (GlGeoGraphics *gelem, m_graphics) {
        gelem->draw();
    }
}
