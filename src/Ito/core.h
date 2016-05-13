#ifndef CORE_H
#define CORE_H

#include "state.h"
#include "objectmanager.h"

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit Core(QObject *parent = 0);

    void setState(State state);
    State state() const {return state;}

    /**
     * @brief Вызвать в цикле отрисовки
     * @param painter
     * @
     */
    void process(QPainter *painter);

signals:
    void stateChanged(const State &state);

private:
    ObjectManager *objectManager;
    //    MapManager *mapManager;
    State state;
};

#endif // CORE_H
