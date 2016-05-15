#ifndef OBJECTSOURCE_H
#define OBJECTSOURCE_H

#include <QObject>

class ObjectSource : public QObject
{
    Q_OBJECT
public:
    explicit ObjectSource(QObject *parent = 0)
        : QObject(parent) {}
};

#endif // OBJECTSOURCE_H
