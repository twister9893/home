#ifndef NETWORK_CONFIGURATOR_H
#define NETWORK_CONFIGURATOR_H

#include "ui_network_configurator.h"
#include "connection_interface.h"

#include <QMainWindow>
#include <QList>
#include <QDomDocument>
#include <QFileDialog>

class NetworkConfigurator : public QMainWindow, Ui::NetworkConfigurator
{
    Q_OBJECT
public:
    explicit NetworkConfigurator(QWidget *parent = 0);

    void setDefaultDir(QString defaultDir);

public slots:
    void open();
    void save();
    void saveAs();
    void quit();
    void setDefault();
    void setDefault(int id);
    void setEdited();
    void setEdited(bool edited);

protected:
    void closeEvent(QCloseEvent *e);

private:
    bool readFromFile(const QString &fileName);
    bool writeToFile(const QString &fileName);
    bool showSaveMessage();

    void loadPlugins();
    void clearWindow();
    void constructWindow(const QDomDocument &config);
    void constructWindow(const QString &xml);

    QDomDocument xmlStringToDom(const QString &xml);
    QWidget* editorFor(const QDomElement &param);
    QLabel* labelFor(const QDomElement &param) const;
    bool setValue(QDomElement &param, int num);

    QList<ConnectionInterface*> _interfaces;
    QDomDocument _config;
    QFileInfo _fileInfo;
    QString _defaultDir;
    bool _isEdited;
};

#endif // NETWORK_CONFIGURATOR_H
