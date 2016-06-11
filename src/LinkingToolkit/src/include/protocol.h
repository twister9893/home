#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QString>

class Protocol
{
public:
    virtual QString name() = 0;
    virtual QString configure() = 0;
    virtual bool open(QString configFileName) = 0;
    virtual bool read(char *data, int *size) = 0;
    virtual bool write(const char *data, int size) = 0;
};
Q_DECLARE_INTERFACE(Protocol, "linkingToolkit.Protocol")

#endif // PROTOCOL_H
