#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QMap>
#include <QPainter>

#include "state.h"
#include "point.h"
#include "ellipse.h"

class ObjectManager : public QObject
{
public:
    ObjectManager();

    bool addObject(Object *object);
    bool removeObject(qint64 id);

    Object * object(qint64 id, bool *ok) const;

    void draw(QPainter *painter);

public slots:
    void setCoreState(const State &state) {this->coreState = state;}

private:
//    void drawTarget(QPainter *painter, const Target & target);
    void drawPrimitive(QPainter *painter, Primitive *primitive);

    QMap<qint64,Object*> objects;
    State coreState;
};

#endif // OBJECTMANAGER_H
