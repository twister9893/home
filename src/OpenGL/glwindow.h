#ifndef GLWINDOW_H
#define GLWINDOW_H

//#include <QOpenGLWindow>
#include <QGLWidget>
#include <QOpenGLFramebufferObject>

class GlWindow : public QGLWidget {
public:
    GlWindow (QWidget * parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    //void paintEvent(QPaintEvent *event);

    //void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);

private:
    void loadMap();

    QOpenGLFramebufferObject *m_mapFbo;

    QSize m_screen;
    QTransform m_globalTransform;
    QPoint m_lastClick;
    double scale;
    double angle;
    double mangle;
    GLfloat posX;
    GLfloat posY;
};

#endif // GLWINDOW_H
