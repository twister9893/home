#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>

class GlWidget : public QOpenGLWidget
{
public:
    GlWidget();
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
};

#endif // GLWIDGET_H
