#ifndef CONNECTION_INTERFACE_H
#define CONNECTION_INTERFACE_H

#include <QString>

class ConnectionInterface
{
public:
    virtual QString name() = 0;
    virtual QString configure() = 0;
    virtual bool open(QString configFileName) = 0;
    virtual bool read(char *data, int *size) = 0;
    virtual bool write(const char *data, int size) = 0;
};
Q_DECLARE_INTERFACE(ConnectionInterface, "linkingToolkit.ConnectionInterface")

#endif // CONNECTION_INTERFACE_H
