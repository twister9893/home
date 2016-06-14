#include "connection.h"

#include <QDomDocument>
#include <QDir>
#include <QDebug>

Connection::Connection(QString configFileName)
    : _opened(false)
{
    open(configFileName);
}

void Connection::open(QString configFileName)
{
    qDebug() << "Opening connection...";

    QFile file(configFileName);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QDomDocument config;
    QString errorMsg;
    int errorLine;
    int errorColumn;
    if(!config.setContent(&file, &errorMsg, &errorLine, &errorColumn)) {
        qCritical() << "Can't read config";
        qCritical() << "Line:" << errorLine << "Colunm:" << errorColumn;
        qCritical() << errorMsg;
        return;
    }
    QDomElement domRoot = config.firstChildElement();

    QDir pluginsDir( "../lib/" );
    QStringList entryList = pluginsDir.entryList(QDir::Files);
    for(int i = 0; i < entryList.size(); i++) {
        QString pluginName = entryList.at(i);
        _loader.setFileName(pluginsDir.absoluteFilePath(pluginName));

        if(_loader.load()) {
            if(ConnectionInterface* interface = qobject_cast<ConnectionInterface*>(_loader.instance())) {
                if(interface->name() == domRoot.attribute("interface")) {
                    _interface = interface;
                    _interface->open(configFileName);
                    _opened = true;
                    break;
                }
            }
        }
    }
}

void Connection::close()
{
    qDebug() << "Closing connection...";
    _loader.unload();
    _opened = false;
}

bool Connection::read(char *data, int *size)
{
    if(_opened)
        return _interface->read(data, size);
    else
        return false;
}

bool Connection::write(const char *data, int size)
{
    if(_opened)
        return _interface->write(data, size);
    else
        return false;
}
