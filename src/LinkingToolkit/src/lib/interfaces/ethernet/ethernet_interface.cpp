#include "ethernet_interface.h"

#include <qplugin.h>
#include <QDebug>

QString EthernetInterface::configure()
{
    QString config = QString::fromUtf8(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            "<!DOCTYPE config>"
            "<config name = \"\" interface = \"%interface\">"
                "<param key = \"ifType\" description = \"Тип протокола\" type = \"enumeration\" value = \"rfc877-x25\">"
                    "<elem>rfc877-x25</elem>"
                    "<elem>ethernet-csmacd</elem>"
                    "<elem>iso88023-csmacd</elem>"
                    "<elem>iso88024-tokenBus</elem>"
                    "<elem>iso88025-tokenRing</elem>"
                "</param>"
                "<param key = \"ifMtu\" description = \"Максимальный размер пакета сетевого уровня\" type = \"integer\" min = \"1\" value = \"128\"/>"
                "<param key = \"ifSpeed\" description = \"Пропускная способность интерфейса\" type = \"integer\" min = \"1\" value = \"100\"/>"
                "<param key = \"ifPhysAddress\" description = \"Физический адрес порта\" type = \"string\" value = \"68:b5:99:eb:a1:38\"/>"
                "<param key = \"ifAdminStatus\" description = \"Статус порта\" type = \"enumeration\" value = \"up\">"
                "<elem>up</elem>"
                "<elem>down</elem>"
                "<elem>testing</elem>"
                "</param>"
            "</config>");
    config.replace("%interface", name());
    return config;
}

bool EthernetInterface::open(QString configFileName)
{
    qDebug() << "open ethernet";
    return true;
}

bool EthernetInterface::read(char *data, int *size)
{
    qDebug() << "read ethernet";
    return true;
}

bool EthernetInterface::write(const char *data, int size)
{
    qDebug() << "write ethernet";
    return true;
}

Q_EXPORT_PLUGIN2(ethernet, EthernetInterface)
