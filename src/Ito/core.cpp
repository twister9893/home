#include "core.h"

#include <QDebug>

Core::Core(QObject *parent)
    : QObject(parent), _markingManager(new MarkingManager(this)), _objectManager(new ObjectManager(this))
{   
    connect(this, SIGNAL(stateChanged(const State&)), _markingManager, SLOT(setCoreState(const State&)));
    connect(this, SIGNAL(stateChanged(const State&)), _objectManager, SLOT(setCoreState(const State&)));
}

void Core::setState(State state)
{
//    if (_state == state)
//        return;

    _state = state;
    emit stateChanged(state);
}

void Core::process(QPainter *painter)
{
    //****FOR TESTING****
//    QPointF pos = _objectManager->object(0)->pos();
//    pos.setX(pos.x()+0.7);
//    pos.setY(pos.y()+0.7);
//    qDebug() << pos.y();
//    _objectManager->object(0)->setPos(pos);
    painter->save();
    painter->setRenderHint(QPainter::HighQualityAntialiasing);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->translate((qreal)(painter->device()->width())/2, (qreal)(painter->device()->height())/2);
    painter->setWindow(0,painter->device()->height(),painter->device()->width(), -painter->device()->height());
    _markingManager->draw(painter);
    _objectManager->draw(painter);
    painter->restore();
}

