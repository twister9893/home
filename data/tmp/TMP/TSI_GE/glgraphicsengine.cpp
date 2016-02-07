#include "glgraphicsengine.h"

GlGraphicsEngine::GlGraphicsEngine() {
    m_painter = new QPainter();
}

GlGraphicsEngine::~GlGraphicsEngine() {

}

QPainter* GlGraphicsEngine::painter() {
    return m_painter;
}
