#ifndef RS422_INTERFACE_H
#define RS422_INTERFACE_H

#include <QObject>

#include "connection_interface.h"

class Rs422Interface : public QObject, public ConnectionInterface
{
    Q_OBJECT
    Q_INTERFACES(ConnectionInterface)
public:
    explicit Rs422Interface(QObject *parent = 0)
        : QObject(parent) {}

    QString name() {return "Rs-422";}
    QString configure();
    bool open(QString configFileName);
    bool read(char *data, int *size);
    bool write(const char *data, int size);
};

#endif // RS422_INTERFACE_H
