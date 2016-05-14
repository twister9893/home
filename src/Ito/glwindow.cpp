#include "glwindow.h"

#include <QDebug>

GlWindow::GlWindow()
    : _core(new Core(this))
{
    setGeometry(200,200,512,512);
    _core->addEllipse(0.0,0.0,100.0,100.0, true);

    _core->addEllipse(50.0,50.0,50.0,50.0, false);
}

void GlWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    _core->process(&painter);
    painter.end();
}

void GlWindow::mouseMoveEvent(QMouseEvent *event) {
//    m_globalTransform.translate(event->x() - m_lastClick.x(), event->y() - m_lastClick.y());
    State state = _core->state();
    qreal dx = (event->x() - _lastClick.x()) * state.scale / qMin(width(), height());
    qreal dy = (event->y() - _lastClick.y()) * state.scale / qMin(width(), height());

    state.offset += QPointF(dx,-dy);
    _core->setState(state);

    _lastClick.setX(event->x());
    _lastClick.setY(event->y());

    repaint();
    event->accept();
}

void GlWindow::mousePressEvent(QMouseEvent *event) {
//    qDebug() << event->button();
    _lastClick.setX(event->x());
    _lastClick.setY(event->y());
    event->accept();
}

void GlWindow::wheelEvent(QWheelEvent * event) {
    State state = _core->state();
    if(event->delta() > 0)
        state.scale /= 2;
    else
        state.scale *= 2;

    if(state.scale >= 1.0 && state.scale <= 2048.0) {
        qDebug() << state.scale;
        _core->setState(state);
        repaint();
    }
    event->accept();
}


