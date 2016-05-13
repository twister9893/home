#include "core.h"

Core::Core(QObject *parent)
    : QObject(parent), objectManager(new ObjectManager)
{   
    connect(this, SIGNAL(stateChanged(const State&)), objectManager, SLOT(setCoreState(const State&)));
}

void Core::setState(State state)
{
    if (this->_state == state)
        return;

    this->_state = state;
    emit stateChanged(state);
}

void Core::process(QPainter *painter)
{
    objectManager->draw(painter);
}

