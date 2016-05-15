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

    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent * event);

private:
    Core *_core;
    QPointF _lastClick;
};

#endif // GLWINDOW_H
