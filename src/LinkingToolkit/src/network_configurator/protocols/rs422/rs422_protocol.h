#ifndef RS422PROTOCOL_H
#define RS422PROTOCOL_H

#include <QObject>

#include "protocol.h"

class Rs422Protocol : public QObject, public Protocol
{
    Q_OBJECT
    Q_INTERFACES(Protocol)
public:
    explicit Rs422Protocol(QObject *parent = 0);

    QString name() {return "Rs-422";}
    QString configure();
    bool open(QString configFileName);
    bool read(char *data, int *size);
    bool write(const char *data, int size);
};

#endif // RS422PROTOCOL_H
