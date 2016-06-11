#ifndef NETWORK_CONFIGURATOR_H
#define NETWORK_CONFIGURATOR_H

#include "ui_network_configurator.h"
#include "protocol.h"
#include "fedit.h"

#include <QList>
#include <QDomDocument>

class NetworkConfigurator : public FileEditor, Ui::NetworkConfigurator
{
    Q_OBJECT
public:
    explicit NetworkConfigurator(QWidget *parent = 0);

public slots:
    void openConfig();
    void saveConfig();
    void quit();
    void setConfigDefault(int id);

protected:
    bool readFromFile(const QString &fileName);
    bool writeToFile(const QString &fileName);
    void clear();

private:
    void loadPlugins();
    void constructWindow(const QDomDocument &config);
    void constructWindow(const QString &xml);
    void clearWindow();
    QDomDocument xmlStringToDom(const QString &xml);
    QWidget* editorFor(const QDomElement &param);
    QLabel* labelFor(const QDomElement &param) const;
    bool setValue(QDomDocument &doc, QDomElement &param, int num);

    QList<Protocol*> _protocols;
    QDomDocument _config;
};

#endif // NETWORK_CONFIGURATOR_H
