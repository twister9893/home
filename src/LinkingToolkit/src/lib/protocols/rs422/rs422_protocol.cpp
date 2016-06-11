#include "rs422_protocol.h"

#include <qplugin.h>
#include <QDebug>

QString Rs422Protocol::configure()
{
    QString config = QString::fromUtf8(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<!DOCTYPE config>"
            "<config name = \"\" protocol = \"%protocol\">"
                "<param name = \"baudRate\" description = \"Скорость передачи данных\" type = \"enumeration\" value = \"1\">"
                    "<elem>9600</elem>"
                    "<elem>19200</elem>"
                "</param>"
                "<param name = \"fParity\" description = \"Контроль четности\" type = \"boolean\" value = \"0\"/>"
                "<param name = \"parity\" description = \"Схема контроля четности\" type = \"enumeration\" value = \"0\">"
                    "<elem>EVENPARITY</elem>"
                    "<elem>MARKPARITY</elem>"
                    "<elem>NOPARITY</elem>"
                    "<elem>ODDPARITY</elem>"
                    "<elem>SPACEPARITY</elem>"
                "</param>"
                "<param name = \"fBinary\" description = \"Двоичный режим обмена\" type = \"boolean\" value = \"1\"/>"
                "<param name = \"byteSize\" description = \"Число информационных бит\" type = \"integer\" min = \"4\" max = \"8\" value = \"8\"/>"
            "</config>");
    config.replace("%protocol", name());
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
