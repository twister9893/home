#include "tsicore.h"

TsiCore::TsiCore()
    : m_graphicsManager(new TsiGraphicsManager())
{
//    setWidth(512);
//    setHeight(512);
    setGeometry(100,100,512,512);
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

//    glColor3f(0.5,0.0,0.0);
//    glBegin(GL_TRIANGLES);
//    glVertex2f(-256,-256);
//    glVertex2f(0.0,256);
//    glVertex2f(256,-256);
//    glEnd;

    m_graphicsManager->process();
}
