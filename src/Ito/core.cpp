#include "core.h"

Core::Core(QObject *parent)
    : QObject(parent), objectManager(new ObjectManager)
{   
    connect(this, SIGNAL(stateChanged(const State&)), objectManager, SLOT(setCoreState(const State&)));
}

void Core::setState(State state)
{
//    if (this->_state == state)
//        return;

    this->_state = state;
    emit stateChanged(state);
}

void Core::process(QPainter *painter)
{
    painter->save();
//    painter->setRenderHint(QPainter::Antialiasing);
    painter->translate((qreal)(painter->device()->width())/2, (qreal)(painter->device()->height())/2);
//    painter->scale(1.0,-1.0);
    painter->setWindow(0,painter->device()->height(),painter->device()->width(), -painter->device()->height());
    objectManager->draw(painter);
    painter->restore();
}

