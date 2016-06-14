#ifndef CONNECTION_H
#define CONNECTION_H

#include <QPluginLoader>
#include <QString>

#include "connection_interface.h"

class Connection
{
public:
    Connection()
        : _opened(false) {}
    Connection(QString configFileName);

    void open(QString configFileName);
    void close();
    bool read(char *data, int *size);
    bool write(const char *data, int size);

    bool isOpened() {return _opened;}

private:
    QPluginLoader _loader;
    ConnectionInterface *_interface;
    bool _opened;
};

#endif // CONNECTION_H
