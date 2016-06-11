#ifndef NETWORK_CONFIGURATOR_H
#define NETWORK_CONFIGURATOR_H

#include "ui_network_configurator.h"
#include "protocol.h"

#include <QWidget>
#include <QList>
#include <QDomDocument>

class NetworkConfigurator : public QWidget, Ui::NetworkConfigurator
{
    Q_OBJECT
public:
    explicit NetworkConfigurator(QWidget *parent = 0);

public slots:
    void showConfig(int id);
    void setConfigDefault() {}
    void saveConfig() {}

private:
    void loadProtocols();
    QWidget* editorFor(QDomElement param);
    QLabel* labelFor(QDomElement param);

    QList<Protocol*> _protocols;
};

#endif // NETWORK_CONFIGURATOR_H
