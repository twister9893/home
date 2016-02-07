#include <QSvgRenderer>
#include <QWheelEvent>
#include <QDebug>
#include <qmath.h>
//#include <QGLShaderProgram>

#include "glwindow.h"

GlWindow::GlWindow (QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f)
    : QGLWidget(parent, shareWidget, f) {
}

void GlWindow::resizeGL(int w, int h) {

}

void GlWindow::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0,0.0,0.0);
    glVertex2f(-0.5,-0.5);

    glColor3f(0.0,1.0,0.0);
    glVertex2f(0.5,-0.5);

    glColor3f(0.0,0.0,1.0);
    glVertex2f(0.0,0.5);
    glEnd();

}

void GlWindow::initializeGL() {
    glClearColor(0.2,0.2,0.2,1.0);
}

/*void GlWindow::paintEvent(QPaintEvent *event) {
    qDebug() << "paintEvent";

    QPainter painter;
    painter.begin(this);

    //painter.setBrush(QBrush(Qt::red));
    //painter.setPen(QPen(QColor(0,200,0)));
    //painter.drawEllipse(QPointF(50,50), 50, 50);
    painter.setTransform(m_globalTransform);
    QSvgRenderer svg;
    svg.load(QString("someIcon.svg"));
    svg.render(&painter);
    //QImage icon("someIcon.svg");
    //painter.drawImage(0,0,icon);

    painter.end();
}
*/
void GlWindow::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << "mouseMoveEvent" << event->x() << event->y();
    m_globalTransform.translate(event->x() - m_lastClick.x(), event->y() - m_lastClick.y());
    m_lastClick.setX(event->x());
    m_lastClick.setY(event->y());
    repaint();
    event->accept();
}

void GlWindow::mousePressEvent(QMouseEvent *event) {
    m_lastClick.setX(event->x());
    m_lastClick.setY(event->y());
    event->accept();
}

void GlWindow::wheelEvent(QWheelEvent * event) {
    qDebug() << "wheelEvent";
    qreal factor = qPow(1.2, event->delta() / 240.0);
    m_globalTransform.scale(factor, factor);
    repaint();
    event->accept();
}

