#include "rs422_protocol.h"

#include <qplugin.h>
#include <QDebug>

Rs422Protocol::Rs422Protocol(QObject *parent) : QObject(parent)
{
}

QString Rs422Protocol::configure()
{
    QString config = QString::fromUtf8(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<!DOCTYPE config>"
            "<config name = \"\">"
                "<param name = \"baudRate\" description = \"Скорость передачи данных\" type = \"enumeration\">"
                    "<value>9600</value>"
                    "<value>19200</value>"
                    "1"
                "</param>"
                "<param name = \"fParity\" description = \"Контроль четности\" type = \"boolean\">"
                    "0"
                "</param>"
                "<param name = \"parity\" description = \"Схема контроля четности\" type = \"enumeration\">"
                    "<value>EVENPARITY</value>"
                    "<value>MARKPARITY</value>"
                    "<value>NOPARITY</value>"
                    "<value>ODDPARITY</value>"
                    "<value>SPACEPARITY</value>"
                    "0"
                "</param>"
                "<param name = \"fBinary\" description = \"Двоичный режим обмена\" type = \"boolean\">"
                    "1"
                "</param>"
                "<param name = \"byteSize\" description = \"Число информационных бит\" type = \"integer\" min = \"4\" max = \"8\">"
                    "8"
                "</param>"
            "</config>");
    return config;
}

bool Rs422Protocol::open(QString configFileName)
{
    qDebug() << "open";
}

bool Rs422Protocol::read(char *data, int *size)
{
    qDebug() << "read";
}

bool Rs422Protocol::write(const char *data, int size)
{
    qDebug() << "write";
}

Q_EXPORT_PLUGIN2(rs422, Rs422Protocol)
