#include "glwindow.h"

#include <QDebug>

GlWindow::GlWindow()
    : _core(new Core(this))
{
    setGeometry(200,200,512,512);
    int64_t id = _core->addEllipse(0.0,0.0,100.0,150.0, true);

    _core->addEllipse(50.0,50.0,100.0,50.0, false, id);

    _core->addTarget(-20.0, 10.0, Target::Iff_Foe, Target::Type_Aircraft);
    _core->addTarget(0.0, 0.0, Target::Iff_Friend, Target::Type_Ship);
    _core->addTarget(20.0, -10.0, Target::Iff_Unidentified, Target::Type_Submarine);
}

void GlWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.save();
    painter.setBrush(QBrush(QColor(20,20,20,50)));
    painter.drawRect(rect());
    painter.restore();

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

void GlWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key()) {
        case Qt::Key_Escape:
            exit(0);
    }
}


