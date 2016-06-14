#include "rs422_interface.h"

#include <qplugin.h>
#include <QDebug>

QString Rs422Interface::configure()
{
    QString config = QString::fromUtf8(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<!DOCTYPE config>"
            "<config name = \"\" interface = \"%interface\">"
                "<param key = \"baudRate\" description = \"Скорость передачи данных\" type = \"enumeration\" value = \"19200\">"
                    "<elem>9600</elem>"
                    "<elem>19200</elem>"
                "</param>"
                "<param key = \"fParity\" description = \"Контроль четности\" type = \"boolean\" value = \"0\"/>"
                "<param key = \"parity\" description = \"Схема контроля четности\" type = \"enumeration\" value = \"EVENPARITY\">"
                    "<elem>EVENPARITY</elem>"
                    "<elem>MARKPARITY</elem>"
                    "<elem>NOPARITY</elem>"
                    "<elem>ODDPARITY</elem>"
                    "<elem>SPACEPARITY</elem>"
                "</param>"
                "<param key = \"fBinary\" description = \"Двоичный режим обмена\" type = \"boolean\" value = \"1\"/>"
                "<param key = \"byteSize\" description = \"Число информационных бит\" type = \"integer\" min = \"4\" max = \"8\" value = \"8\"/>"
            "</config>");
    config.replace("%interface", name());
    return config;
}

bool Rs422Interface::open(QString configFileName)
{
    qDebug() << "open rs422";
    return true;
}

bool Rs422Interface::read(char *data, int *size)
{
    qDebug() << "read rs422";
    return true;
}

bool Rs422Interface::write(const char *data, int size)
{
    qDebug() << "write rs422";
    return true;
}

Q_EXPORT_PLUGIN2(rs422, Rs422Interface)
