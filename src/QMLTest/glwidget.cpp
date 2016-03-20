#include "glwidget.h"

GlWidget::GlWidget()
{

}

void GlWidget::initializeGL()
{
    glClearColor(0.5,0.5,0.5,1.0);
}

void GlWidget::resizeGL(int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3b(255,0,0);
    glVertex2f(-0.5,-0.5);
    glColor3b(0,255,0);
    glVertex2f(0,0.5);
    glColor3b(0,0,255);
    glVertex2f(0.5,-0.5);
    glEnd();
}
