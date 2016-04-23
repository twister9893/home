#include "tsicore.h"

TsiCore::TsiCore()
    : m_graphicsManager(new TsiGraphicsManager())
{
}

TsiCore::~TsiCore()
{
    delete m_graphicsManager;
}

void TsiCore::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1.0);
}

void TsiCore::resizeGL(int w, int h)
{
//    m_screen.setWidth(w);
//    m_screen.setHeight(h);
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TsiCore::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_graphicsManager->process();
}
