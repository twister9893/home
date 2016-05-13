#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QGLWidget>
#include <QPaintEvent>
#include "core.h"

class GlWindow : public QGLWidget
{
public:
    GlWindow();

protected:
//    void initializeGL();
//    void resizeGL(int w, int h);
//    void paintGL();
//    void resizeEvent(QResizeEvent *e) {
//    }

    void paintEvent(QPaintEvent *) {
        QPainter painter(this);
        core->process(&painter);
    }

private:
    Core *core;
};

#endif // GLWINDOW_H
