#ifndef CORE_H
#define CORE_H

#include "state.h"
#include "objectmanager.h"

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State _state READ state WRITE setState NOTIFY stateChanged)
public:
    explicit Core(QObject *parent = 0);

    void setState(State _state);
    State state() const {return _state;}

    /**
     * @brief Вызвать в цикле отрисовки
     * @param painter
     * @
     */
    void process(QPainter *painter);


    void addEllipse(qreal x, qreal y, qreal width, qreal height) {
        Ellipse *ellipse = new Ellipse(1, QPointF(x,y), QRectF(0.0,0.0,width,height));
        objectManager->addObject(ellipse);
    }


signals:
    void stateChanged(const State &_state);

private:
    ObjectManager *objectManager;
    //    MapManager *mapManager;
    State _state;
};

#endif // CORE_H
