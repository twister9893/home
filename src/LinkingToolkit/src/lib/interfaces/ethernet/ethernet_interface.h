#ifndef ETHERNET_INTERFACE_H
#define ETHERNET_INTERFACE_H

#include <QObject>

#include "connection_interface.h"

class EthernetInterface : public QObject, public ConnectionInterface
{
    Q_OBJECT
    Q_INTERFACES(ConnectionInterface)
public:
    explicit EthernetInterface(QObject *parent = 0)
        : QObject(parent) {}

    QString name() {return "Ethernet";}
    QString configure();
    bool open(QString configFileName);
    bool read(char *data, int *size);
    bool write(const char *data, int size);
};

#endif // ETHERNET_INTERFACE_H
