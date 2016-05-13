#include "core.h"

Core::Core(QObject *parent)
    : QObject(parent), objectManager(new ObjectManager)
{   
    connect(this, SIGNAL(stateChanged(const State&)), objectManager, SLOT(setCoreState(const State&)));
}

void Core::setState(State state)
{
    if (this->state == state)
        return;

    this->state = state;
    emit stateChanged(state);
}

void Core::process(QPainter *painter)
{
    objectManager->draw(painter);
}

